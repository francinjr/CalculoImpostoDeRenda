#include <iostream>
#include <string>
#include "../curl/include/curl/curl.h"
#include "../json.hpp"

using namespace std;

// Em resumo, o método abaixo pega o json feito na requisição
static size_t WriteCallback(char *contents, size_t size, size_t nmemb, char *buffer_in)
{
	((string*)buffer_in)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

float CotacaoMoedas(string sMoeda, float ganhos)
{
	// Declarações do curl da biblioteca curl para fazer as requisições http
	using json = nlohmann::json;
	
    CURL *curl;
    CURLcode res;
    string readBuffer;
    
    curl = curl_easy_init();
    if(curl)
    {
    	float nGanhos = ganhos;
    	string moeda = sMoeda;
    	string reqMoeda;

		// Abaixo é o corpo da requisição http, e reqMoeda recebe a requisição da moeda que foi escolhida e pede a API para que traga a conversão para real brasileiro
    	reqMoeda = "https://economia.awesomeapi.com.br/last/" + moeda + "-BRL";
        curl_easy_setopt(curl, CURLOPT_URL, reqMoeda.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        
        // Manipulção do json que foi pego na requisição, lembrando que está sendo usada a biblioteca json.hpp para manipular json
        // Além disso, foi feita uma manipulação com o nome da propriedade que vai ser acessada dévido as regras da API
        json j = json::parse(readBuffer);
        
        string moedaParaReal = moeda + "BRL";

		//  Pegando o valor que uma unidade daquela moeda tem, transformada para real
        float cotacao = stod(j.at(moedaParaReal).at("bid").get<string>());

		// E finalmente retornando o valor que usuário digitou, mas agora transformado em real brasileiro
        return cotacao * nGanhos;
    }
}
