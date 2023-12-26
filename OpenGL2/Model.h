#pragma once

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Textura.h"

class Model
{
public:
	Model();

	void carregarModel(const std::string& nomeArquivo);
	void renderizarModel();
	void limparModel();

	~Model();

private:
	std::vector<Mesh*> listaMesh;
	std::vector<Textura*> listaTex;
	std::vector<unsigned int> meshParaTex;

	void carregarNode(aiNode* node, const aiScene* scene);
	void carregarMesh(aiMesh* mesh, const aiScene* scene );
	void carregarMaterial(const aiScene* scene);
 
};

