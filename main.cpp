#include <iostream>
#include <string>
#include <cctype>
#include <locale>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Funcoes/CotacaoMoedas.cpp"

// Observações importantes: Para compilar o projeto, é necessário clicar em Tools na parte superior do Dev-C++ e clicar Compile Options. No primeiro campo coloque -std=gnu++11 e no segundo coloque -Icurl/include -Lcurl/lib -lcurl
//As caixinhas devem ser marcadas, então clique em Ok. Sempre que for compilar o programa, compile estando no arquivo main ou então não vai funcionar. 
using namespace std;

struct rendimentosTributaveis {
    float salario;
    float pensao;
    float aposentadoria;
    float aluguel;
    float rendimento_anual;
};

void maiorOuIgualaZero(float valor);
void getDadosRT(rendimentosTributaveis* ptr);
float retornaLegal(float* ptr, float* ptr2);
float retornaSimples(float* ptr);
float getValor(string msg);
void despesasDedutiveis(float* ptr_desconto, float* ptr_inss, float* ptr_qnt_dependente, float* ptr_pensao_alimenticia, float* ptr_educacao, float* ptr_saude);
void chamarImposto(float* ptr);
void chamarRestituicao(float* ptr);
void cotacaoMoeda();

int main()
{
	
    setlocale(LC_ALL, "pt_BR.UTF-8");
    rendimentosTributaveis rT;
    float totalRendimentoAnual;
    float totalRendimentoAnual2;
    float imposto = 0;
    string nome;
    float deducaoDD;
    float fonte;
    float restituicao;
    float descontoGov = 0.2;
    float desconto, inss, qnt_dependente, pensao_alimenticia, educacao, saude;
    
    cout << "Insira o seu nome completo: ";
    getline(cin, nome);
    
    cout << endl;

    getDadosRT(&rT);

    cout << endl;

    despesasDedutiveis(&desconto, &inss, &qnt_dependente, &pensao_alimenticia, &educacao, &saude);
    deducaoDD = desconto;

    cout << endl;

    cout << "Digite o valor retido na fonte: ";
    cin >> fonte;

    cout << endl;

    totalRendimentoAnual = retornaLegal(&rT.rendimento_anual, &deducaoDD);
    totalRendimentoAnual2 = retornaSimples(&rT.rendimento_anual);

    cout << "Declaraçao Legal: " << endl;

    if (totalRendimentoAnual > 22847.76) {
        if (totalRendimentoAnual >= 22847.77 && totalRendimentoAnual <= 33919.80) {
            imposto = (totalRendimentoAnual * 0.075f) - 1713.58;
            restituicao = imposto - fonte;
            if (restituicao > 0) {
                chamarImposto(&imposto);
            }
            else {
                chamarRestituicao(&restituicao);
            }
        }
        else if (totalRendimentoAnual >= 33919.81 && totalRendimentoAnual <= 45012.60) {
            imposto = (totalRendimentoAnual * 0.15f) - 4257.57;
            restituicao = imposto - fonte;
            if (restituicao > 0) {
                chamarImposto(&imposto);
            }
            else {
                chamarRestituicao(&restituicao);
            }
        }
        else if (totalRendimentoAnual >= 45012.61 && totalRendimentoAnual <= 55976.16) {
            imposto = (totalRendimentoAnual * 0.225f) - 7633.51;
            restituicao = imposto - fonte;
            if (restituicao > 0) {
                chamarImposto(&imposto);
            }
            else {
                chamarRestituicao(&restituicao);
            }
        }
        else {
            imposto = (totalRendimentoAnual * 0.275f) - 10432.32;
            restituicao = imposto - fonte;
            if (restituicao > 0) {
                chamarImposto(&imposto);
            }
            else {
                chamarRestituicao(&restituicao);
            }
        }
    }
    else {
        restituicao = totalRendimentoAnual - fonte;
        if (restituicao > 0) {
            chamarImposto(&imposto);
        }
        else {
            chamarRestituicao(&restituicao);
        }
    }

    cout << "Declaraçao Simplificada: " << endl;

    if (totalRendimentoAnual2 > 22847.76) {
        if (totalRendimentoAnual2 >= 22847.77 && totalRendimentoAnual2 <= 33919.80) {
            imposto = (totalRendimentoAnual2 * 0.075f) - 1713.58;
            restituicao = imposto - fonte;
            if (restituicao > 0) {
                chamarImposto(&imposto);
            }
            else {
                chamarRestituicao(&restituicao);
            }
        }
        else if (totalRendimentoAnual2 >= 33919.81 && totalRendimentoAnual2 <= 45012.60) {
            imposto = (totalRendimentoAnual2 * 0.15f) - 4257.57;
            restituicao = imposto - fonte;
            if (restituicao > 0) {
                chamarImposto(&imposto);
            }
            else {
                chamarRestituicao(&restituicao);
            }
        }
        else if (totalRendimentoAnual2 >= 45012.61 && totalRendimentoAnual2 <= 55976.16) {
            imposto = (totalRendimentoAnual2 * 0.225f) - 7633.51;
            restituicao = imposto - fonte;
            if (restituicao > 0) {
                chamarImposto(&imposto);
            }
            else {
                chamarRestituicao(&restituicao);
            }
        }
        else {
            imposto = (totalRendimentoAnual2 * 0.275f) - 10432.32;
            restituicao = imposto - fonte;
            if (restituicao > 0) {
                chamarImposto(&imposto);
            }
            else {
                chamarRestituicao(&restituicao);
            }
        }
    }
    else {
        restituicao = totalRendimentoAnual2 - fonte;
        if (restituicao > 0) {
            chamarImposto(&imposto);
        }
        else {
            chamarRestituicao(&restituicao);
        }
    }
    
    FILE* arquivo = fopen("declaracao_imposto.csv", "a");
	
	if (arquivo == nullptr) {
		perror("Erro ao abrir o arquivo");
		exit(EXIT_FAILURE);
	}
	
	fseek(arquivo, 0, SEEK_END);
	if (ftell(arquivo) == 0) {
		fprintf(arquivo, "Nome; Salário; Aposentadoria; Aluguel; Pensão; Rendimento Anual; Valor Retido na fonte; Contribuição Previdenciária; Quantidade de Dependentes; Pensão Alimentícia; Gastos com Educação; Gastos com Saúde; Imposto a pagar; Restituição\n");
	}
	
	fprintf(arquivo, "%s; %.2f; %.2f; %.2f; %.2f; %.2f; %.2f; %.2f; %.f; %.2f; %.2f; %.2f; %.2f; %.2f\n", nome.c_str(), rT.salario, rT.aposentadoria, rT.aluguel, rT.pensao, rT.rendimento_anual, fonte, inss, qnt_dependente, pensao_alimenticia, educacao, saude, imposto, restituicao);
	
	fclose(arquivo);
	
	cotacaoMoeda();
	
}

float retornaLegal(float* ptr, float* ptr2) {
    float total;
    cout << "Rendimento tributavel anual: " << *ptr << endl;
    cout << "Despesas dedutiveis: " << *ptr2 << endl;
    total = *ptr - *ptr2;
    cout << "DEDUÇAO: " << total << endl << endl;
    return total;
}

float retornaSimples(float* ptr) {
    float total;
    cout << "Rendimento tributavel anual: " << *ptr << endl;
    total = *ptr - (*ptr * 0.2);
    cout << "DEDUÇAO: " << total << endl << endl;
    return total;
}

void getDadosRT(rendimentosTributaveis* ptr) {

    ptr->salario = getValor("do salario");
    ptr->aposentadoria = getValor("da aposentadoria");
    ptr->aluguel = getValor("do aluguel");
    ptr->pensao = getValor("da pensao");
    ptr->rendimento_anual = ptr->salario + ptr->aposentadoria + ptr->aluguel + ptr->pensao; 
}

float getValor(string msg)
{
    float valor;
    do {
        cout << "Digite o valor " << msg << ": (se nao houver, digite 0.) ";
        cin >> valor;
        if (valor < 0) {
            cout << "Valor invalido (deve ser um número maior ou igual a zero)." << endl;
        }
    } while (valor < 0);
    return valor;
}

void maiorOuIgualaZero(float valor) {
    while (valor < 0) {
        cout << "Valor invalido (deve ser um número maior ou igual a zero)." << endl;
        cin >> valor;
    }
}

void despesasDedutiveis(float* ptr_desconto, float* ptr_inss, float* ptr_qnt_dependente, float* ptr_pensao_alimenticia, float* ptr_educacao, float* ptr_saude) {

    char sn;
    int qnt_dependente;
    float pensao_alimenticia;
    float educacao;
    float saude;
    float inss;
    float desconto = 0;
    
    *ptr_desconto = desconto;

    cout << "Digite o valor da contribuiçao previdenciaria oficial: ";
    cin >> inss;
    maiorOuIgualaZero(inss);
    *ptr_inss = inss;
    *ptr_desconto += inss;

    cout << "Possui dependente(s)? [S/N] ";
    cin >> sn;
    sn = toupper(sn);
    if (sn == 'S') {
        cout << "Insira o numero de dependentes: ";
        cin >> qnt_dependente;
        maiorOuIgualaZero(qnt_dependente);
        *ptr_qnt_dependente = qnt_dependente;
        *ptr_desconto += (qnt_dependente * 2275.08f);
    }

    cout << "Realiza pagamento de pensao alimenticia? [S/N] ";
    cin >> sn;
    sn = toupper(sn);
    if (sn == 'S') {
        cout << "Digite o valor do pagamento: ";
        cin >> pensao_alimenticia;
        *ptr_pensao_alimenticia = pensao_alimenticia;
        maiorOuIgualaZero(pensao_alimenticia);
        *ptr_desconto += pensao_alimenticia;
    }

    cout << "Possui gastos com educaçao? [S/N] ";
    cin >> sn;
    sn = toupper(sn);
    if (sn == 'S') {
        cout << "Digite o valor dos gastos: ";
        cin >> educacao;
        *ptr_educacao = educacao;
        maiorOuIgualaZero(educacao);
        *ptr_desconto += educacao;
    }

    cout << "Possui gastos com saude? [S/N] ";
    cin >> sn;
    sn = toupper(sn);
    if (sn == 'S') {
        cout << "Digite o valor dos gastos: ";
        cin >> saude;
        maiorOuIgualaZero(saude);
        *ptr_saude = saude;
        if (saude >= 3561.50) {
            *ptr_desconto += 3561.50;
        }
        else {
            *ptr_desconto += saude;
        }
    } 
}

void chamarImposto(float *ptr) {
    cout << "Imposto a pagar incidente nos rendimentos tributaveis: " << *ptr << endl;
    cout << "Sem nenhum valor a restituir." << endl << endl;
}

void chamarRestituicao(float* ptr) {
    cout << "Valor a restituir: " << *ptr * (-1) << endl;
    cout << "Sem imposto a pagar." << endl << endl;
}

void cotacaoMoeda(){
	    // Declaração das variáveis e chamada da função conversora de moedas. O código abaixo foi um teste da API de cotação de moeda que deu certo, então para fazer a conversão de moedas basta chamar o método CotacaoMoeda()
    // enviando para a função a sigla da moeda (exemplo: dolar é USD) e o quanto ganha com aquela moeda, o retorno será o valor convertido em reais.
    string sMoeda;
    float ganhos;
    
    cout << "Digite a sigla de sua moeda(exemplo: dolar eh USD)" << endl;
    cin >> sMoeda;
    cout << "Digite quanto voce ganha em " << sMoeda << endl;
    cin >> ganhos;
    cout << "O valor que voce ganha em reais eh: R$ " << CotacaoMoedas(sMoeda, ganhos) << endl;
    // cotacao de moedas vai até aqui. Essas entradas de dados podem ser implementadas na função CotacaoMoeda() depois, se necessário.
}
