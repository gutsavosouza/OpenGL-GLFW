#include "Model.h"

Model::Model() {

}

void Model::carregarModel(const std::string& nomeArquivo) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(nomeArquivo, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (!scene) {
		//printf("Erro ao carregar o modelo(%s): %s\n", nomeArquivo, importer.GetErrorString());
		return;
	}

	carregarNode(scene->mRootNode, scene);
	carregarMaterial(scene);
}

void Model::renderizarModel() {
	for (size_t i = 0; i < listaMesh.size(); i++) {
		unsigned int materialIndex = meshParaTex[i];

		if (materialIndex < listaTex.size() && listaTex[materialIndex]) {
			listaTex[materialIndex]->usarTextura();
		}

		listaMesh[i]->renderizarMesh();
	}
}

void Model::limparModel() {
	for (size_t i = 0; i < listaMesh.size(); i++) {
		if (listaMesh[i]) {
			delete listaMesh[i];
			listaMesh[i] = nullptr;
		}
	}

	for (size_t i = 0; i < listaTex.size(); i++) {
		if (listaTex[i]) {
			delete listaTex[i];
			listaTex[i] = nullptr;
		}
	}
}

void Model::carregarNode(aiNode* node, const aiScene* scene) {
	for (size_t i = 0; i < node->mNumMeshes; i++) {
		carregarMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

	for (size_t i = 0; i < node->mNumChildren; i++) {
		carregarNode(node->mChildren[i], scene);
	}
}

void Model::carregarMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;

	for (size_t i = 0; i < mesh->mNumVertices; i++) {
		vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });

		if (mesh->mTextureCoords[0]) {
			vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
		}
		else {
			vertices.insert(vertices.end(), { 0.0f, 0.0f });
		}

		vertices.insert(vertices.end(), { -mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z });
	}

	for (size_t i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	Mesh* novaMesh = new Mesh();
	novaMesh->criarMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
	listaMesh.push_back(novaMesh);
	meshParaTex.push_back(mesh->mMaterialIndex);
}

void Model::carregarMaterial(const aiScene* scene) {
	listaTex.resize(scene->mNumMaterials);
	for (size_t i = 0; i < scene->mNumMaterials; i++) {
		aiMaterial* material = scene->mMaterials[i];

		listaTex[i] = nullptr;

		if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == aiReturn_SUCCESS) {
				int idx = std::string(path.data).rfind("\\");
				std::string nomearquivo = std::string(path.data).substr(idx + 1);

				std::string texPath = std::string("Texturas/") + nomearquivo;

				listaTex[i] = new Textura(texPath.c_str());

				if (!listaTex[i]->carregarTextura()) {
					//printf("Erro ao carregar a textura em: %s\n", texPath);
					delete listaTex[i];
					listaTex[i] = nullptr;
				}
			}
		}
		if (!listaTex[i]) {
			listaTex[i] = new Textura("Texturas/metal1.png");
			listaTex[i]->carregarTexturaAlpha();
		}
	}
}

Model::~Model() {
	limparModel();
}
