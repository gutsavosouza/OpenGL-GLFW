#version 330

in vec4 vCor;
in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 cor;

const int MAX_LUZ_PONTUAL_CONT = 3;
const int MAX_LUZ_HOLOFOTE_CONT = 3;

struct Luz {
	vec3 cor;
	float intensidadeAmbiente;
	float intensidadeDifusao;
};

struct luzDirecional {
	Luz base;
	vec3 direcao;
};

struct luzPontual {
	Luz base;
	vec3 posicao;
	float constante;
	float linear;
	float expoente;
};

struct luzHolofote {
	luzPontual base;
	vec3 direcao;
	float borda;
};

struct Material {
	float intensidadeEspecular;
	float brilho;
};

uniform int contLuzPontual;
uniform int contLuzHolofote;

uniform luzDirecional LD;
uniform luzPontual LP[MAX_LUZ_PONTUAL_CONT];
uniform luzHolofote LH[MAX_LUZ_HOLOFOTE_CONT];

uniform sampler2D texture;
uniform Material material;

uniform vec3 posOlho;

vec4 calcLuzPorDirecao(Luz luz, vec3 direcao) {
	vec4 corAmbiente = vec4(luz.cor, 1.0f) * luz.intensidadeAmbiente;

	float fatorDifusao = max(dot(normalize(Normal), normalize(direcao)), 0.0f);
	vec4 difusaoCor = vec4(luz.cor * luz.intensidadeDifusao * fatorDifusao, 1.0f);

	vec4 corEspecular = vec4(0, 0, 0, 0);

	if(fatorDifusao > 0.0f){
		vec3 fragParaOlho = normalize(posOlho - FragPos);
		vec3 vetorReflexao = normalize(reflect(direcao, normalize(Normal)));

		float fatorEspecular = dot(fragParaOlho, vetorReflexao);
		if(fatorEspecular > 0){
			fatorEspecular = pow(fatorEspecular, material.brilho);
			corEspecular = vec4(luz.cor * material.intensidadeEspecular * fatorEspecular, 1.0f);
		}
	}

	 return (corAmbiente + difusaoCor + corEspecular);
}

vec4 calcLuzDirecional() {
	return calcLuzPorDirecao(LD.base, LD.direcao);
}

vec4 calcLuzPontual(luzPontual luz){
	vec3 direcao = FragPos - luz.posicao;
	float distancia = length(direcao);
	direcao = normalize(direcao);

	vec4 cor = calcLuzPorDirecao(luz.base, direcao);

	float atenuacao = luz.expoente * distancia * distancia
					 + luz.linear * distancia 
					 + luz.constante;

	return (cor / atenuacao);
}

vec4 calcLuzHolofote(luzHolofote luz) {
	vec3 rayDirecao = normalize(FragPos - luz.base.posicao);

	float fatorHolofote = dot(rayDirecao, luz.direcao);

	if(fatorHolofote > luz.borda) { 
		vec4 cor = calcLuzPontual(luz.base);

		return cor * (1.0f - (1.0f - fatorHolofote) * (1.0f / (1.0f - luz.borda)));
	} else {
		return vec4(0, 0, 0, 0);
	}
}

vec4 calcLuzesHolofote() {
	vec4 corTotal = vec4(0, 0, 0, 0);
	for(int i = 0; i < contLuzHolofote; i++) {
		corTotal += calcLuzHolofote(LH[i]);
	}
	return corTotal;
}

vec4 calcLuzesPontual() {
	vec4 corTotal = vec4(0, 0, 0, 0);
	for(int i =0; i < contLuzPontual; i++) {
		corTotal += calcLuzPontual(LP[i]);
	}

	return corTotal;
 }

void main(){
	vec4 corFinal = calcLuzDirecional() + calcLuzesPontual() + calcLuzesHolofote();

	cor = texture(texture, texCoord) * corFinal;
}