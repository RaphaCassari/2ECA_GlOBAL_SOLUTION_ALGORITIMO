
/*
By: Raphael Cassari Benedicto  RM:85454
*/

#include <iostream>
#include <locale>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

using namespace std;

#define N_Clientes 100 //número de clientes máximo da clínica
#define N_MED 48       //número de medidas registradas por dia
#define NC 20          //número de caracteres das strings usadas no programa
#define NC_LINHA 80
#define NC_SN 4 //número de caracteres das strings de resposta sim e nao

/*
Tarefa 1: Especificar o molde (formato) de: struct medida e struct cliente.
Definir tipo de dado TipoMedida e TipoCliente baseadas nos moldes especificados.
*/

struct medida
{
    char hora[NC]; // rever o tipo
    int sistole;
    int diastole;
    int frequencia;
    int glicemia;
};

struct cliente
{
    char id[NC];
    int idade; // rever
    char sexo[NC];
    char hipertensao[NC_SN];
    char diabetes[NC_SN];
};

typedef struct medida TipoMedida;
typedef struct cliente TipoCliente;

/*
Tarefa 2: Inserir função com método de busca mais adequado para
encontrar no vetor de clientes, o paciente com id passado como parâmetro
*/

int busca_binaria(char id[NC], TipoCliente vet[])
{
    int i_baixo = 0, i_alto = N_Clientes - 1, i_medio;
    int achou = 0;
    int pos = -1;

    while (achou != 1 && i_baixo <= i_alto)
    {
        i_medio = (i_baixo + i_alto) / 2;
        if (strcmp(id, vet[i_medio].id) != 0)
        {
            pos = i_medio;
            achou = 1;
        }
        else
        {
            if (id < vet[i_medio].id)
                i_alto = i_medio - 1;
            else
                i_baixo = i_medio + 1;
        }
    }
    return (pos);
}

/*
Tarefa 3:Inserir função com método de busca mais adequado para consultar no arquivo de medidas.
A função deve ser modificada em relação a que foi estudada em aula para que apresente na tela
de saída todas as medidas com nível de glicose passada como parâmetro
*/

void mostrar_glicose(int chave, TipoMedida vet[])
{
    int i, ne = 0;
    for (i = 0; i < N_MED; i++)
    {
        if (vet[i].glicemia == chave)
        {
            cout << "Hora:" << vet[i].hora << "\t"
                 << "Sistole:" << vet[i].sistole << "\t"
                 << "Diastole:" << vet[i].diastole << "\t"
                 << "Frequencia:" << vet[i].frequencia << "\t"
                 << "Glicemia:" << vet[i].glicemia << endl;
        }
    }
}

/*
Tarefa 4:Inserir função com método de ordenação mais adequado que faça a ordenação do vetor de
medidas em ordem decrescente de pulsação.
*/

void ordenacao_pulsacao(TipoMedida vetor[])
{
    int aux, i, j;
    int comp = 0;
    int troca = 1; /* supõe realizar troca */
    for (i = 0; i < N_MED - 1 && troca == 1; i++)
    {
        troca = 0; /* supõe não realizar troca */
        for (j = 0; j < N_MED - i - 1; j++)
        {
            comp++;
            if (vetor[j].frequencia < vetor[j + 1].frequencia)
            {
                aux = vetor[j].frequencia;
                vetor[j].frequencia = vetor[j + 1].frequencia;
                vetor[j + 1].frequencia = aux;
                troca = 1; /*registra que houve troca na iteração*/
            }
        }
    }
}

int main()
{
    setlocale(LC_ALL, "");
    FILE *arq;
    int i, np, nm, n, resp;
    int maior = 0; //variável que armazena o maior valor de glicemia
    int cont = 0;  //variável que armazena quantas medidas de pressão com valores acima de 14:10
    char id[NC];
    char aux[NC_LINHA];
    TipoMedida medidas[N_MED];
    TipoCliente clientes[N_Clientes];

    arq = fopen("ListaClientes.txt", "rt");
    if (arq == NULL)
    {
        printf("Problemas na abertura do arquivo\n");
        return -1;
    }
    else
    {
        np = 0;
        fgets(aux, NC_LINHA, arq);
        cout << aux << endl;
        while (fscanf(arq, "%s%i%s%s%s", clientes[np].id, &clientes[np].idade, clientes[np].sexo, clientes[np].hipertensao, clientes[np].diabetes) != EOF)
        {
            cout << clientes[np].id << "\t\t " << clientes[np].idade << " \t" << clientes[np].sexo << "\t" << clientes[np].hipertensao << "\t\t" << clientes[np].diabetes << endl;
            np++;
        }
        fclose(arq);
        do
        {
            cout << "\n************  Lista de Clientes com Registros Atualizados *********************\n";
            cout << "\t 1393\n\t 1492\n ";
            cout << "Qual ID de cliente que quer analisar: ";
            cin.getline(id, 80);
            cout << "cliente a consultar: " << id << endl;
            /*
TAREFA 5:Chama a função desenvolvida na TAREFA 2 para obter a posição do registro do cliente
no vetor de pacientes passando id como parâmetro. Variável n recebe o retorno da função.
*/

            n = busca_binaria(id, clientes);

            cout << "ID: " << clientes[n].id << " idade: " << clientes[n].idade << " sexo: " << clientes[n].sexo << " hipertensao: " << clientes[n].hipertensao << " diabetes: " << clientes[n].diabetes << endl;
            system("pause");

            strcat(id, "_01_06");
            strcat(id, ".txt");
            arq = fopen(id, "rt");
            if (arq == NULL)
            {
                printf("Problemas na abertura do arquivo\n");
                return -1;
            }
            nm = 0;
            fgets(aux, NC_LINHA, arq);
            while (nm < N_MED)
            {
                fscanf(arq, "%s%i%i%i%i", medidas[nm].hora, &medidas[nm].sistole, &medidas[nm].diastole, &medidas[nm].frequencia, &medidas[nm].glicemia);
                nm++;
            }
            fclose(arq);

            do
            {
                system("cls");
                cout << "1) Encontrar maior medida de glicemia registrada e apresentar todas as ocorrencias.\n";
                cout << "2) Apresentar quantas medidas foram registradas de pressao sistolica a partir de 14 mmHg e diastolica a partir de 10 mmHg .\n";
                cout << "3) Apresentar os 20 registros com os maiores valores de pulsacao.\n";
                cout << "4) Encerrar analise do cliente.\n";
                cout << "\t Digite a opcao desejada: ";
                cin >> resp;
                cin.ignore();
                switch (resp)
                {
                case 1:
                    system("cls");
                    /*
TARFEFA 6: Inserir trecho de programa que encontra a maior medida de glicose do cliente, apresentando
todos os registros de medida nos quais foram registradas essa medida (a maior).
Para isso deve ser feita a chamada da função desenvolvida na TAREFA 3
*/
                    for (i = 0; i < N_MED; i++)
                    {
                        if (medidas[i].glicemia > maior)
                            maior = medidas[i].glicemia;
                    }
                    mostrar_glicose(maior, medidas);

                    system("pause");
                    break;
                case 2:
                    system("cls");
                    /*
TARFEFA 7: Inserir trecho de programa que apresentar o número de medidas de pressão em que a
pressão sistólica tem valor acima (inclusive) de 14 mmHg e diastólica tem valor acima (inclusive)
de 10 mmHg.
*/
                    for (i = 0; i < N_MED; i++)
                    {
                        if (medidas[i].sistole >= 14 && medidas[i].diastole >= 10)
                        {
                            cout << "Hora: " << medidas[i].hora << "\t"
                                 << "Sistole: " << medidas[i].sistole << "\t"
                                 << "Diastole: " << medidas[i].diastole << "\t"
                                 << "Frequencia: " << medidas[i].frequencia << "\t"
                                 << "Glicemia: " << medidas[i].glicemia << endl;
                            cont++;
                        }
                    }
                    cout << "Numero de vezes que a pressao sistolica tem valor acima de 14 mmHg e diastolica tem valor acima de 10 mmHg: " << cont++ << endl;

                    system("pause");
                    break;
                case 3:
                    system("cls");
                    /*
TARFEFA 8: Chama a função desenvolvida na TAREFA 4 para ordenar os registros no vetor de medidas em ordem
decrescente de pulsação. São apresentadas as 20 registros com os maiores valores de pulsação.
*/

                    ordenacao_pulsacao(medidas);

                    for (i = 0; i < 20; i++)
                    {
                        cout << "Hora: " << medidas[i].hora << "\t"
                             << "Sistole: " << medidas[i].sistole << "\t"
                             << "Diastole: " << medidas[i].diastole << "\t"
                             << "Frequencia: " << medidas[i].frequencia << "\t"
                             << "Glicemia: " << medidas[i].glicemia << endl;
                    }

                    system("pause");
                    break;
                case 4:
                    cout << "Encerrando a avaliacao. \nGerar atualização do prontuario!\n\n";
                    break;
                default:
                    cout << "opcao invalida\n";
                }
            } while (resp != 4);
            cout << "Deseja analisar mais um cliente? (1-sim /Qualquer outro valor - nao): ";
            cin >> resp;
            cin.ignore();
        } while (resp == 1);
    }
    return 0;
}
