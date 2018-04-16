#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>

#define maxest 4
#define TAM 13
#define MAX 50


void textcolor (int color){
  SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), color );
}

///////////////////// PROTóTIPOS //////////////////////////////////
int menu();

int data_do_arquivo (int dia, int mes, int ano);
void exibir(dados, produto);
void voltar();
void func1(dados, produto);
void func2(dados,produto);
void func3(dados);
void func4(produto,dados);
void func5(produto,dados);

//////////////VARIÁVEIS GLOBAIS //////////////////
float dados[MAX][TAM];
char produto[MAX][TAM];

////////////////////////////////////// MENU ///////////////////////////////
int menu()
{

    setlocale(LC_ALL,"portuguese");

/////////////*  VARIAVEIS  *////////////////

    int op, i, j, maxlin[5];

///////////////////// INICIALIZANDO MATRIZ COM OS DADOS NUMÉRICOS DE CADA INFORMAÇÃO ////////////////////////////
        do{
                textcolor(10);
                printf("\n\n\n\t\t.::  Centro de Análise de Tratamento de Efluêntes  ::.\n\n");
                textcolor(15);
                printf("\t(1) Carregar dados da estação\n");
                printf("\t(2) Principal resíduo produzido por estação\n");
                printf("\t(3) Total de resíduos tratados por estação\n");
                printf("\t(4) Consulta por resíduo: maior e menor consumo de reagentes\n");
                printf("\t(5) Listagem de Eficiência: Resíduo x Estação (todos os resíduos)\n");
                printf("\t(6) Encerrar\n\n");
                printf("\tOpção: ");
                scanf("%d", & op);
                fflush(stdin);
                if(op <=0 || op >=7){

                        textcolor(14);
                        printf("\n\n\7 Opção inválida! Tente novamoente.\n\n\n");
                        textcolor(15);
                        system("pause");
                        system("cls");
                    }
        }while(op <= 0 || op >= 7);

        switch (op){

                    case 1:
                        system("cls");
                        func1(dados, produto);
                        break;

                    case 2:
                        func2(dados,produto);
                        break;

                    case 3:
                        func3(dados);
                        break;

                    case 4:
                        func4(produto,dados);
                        break;

                    case 5:
                        func5(produto,dados);
                        break;

                    case 6:
                        voltar();
                        break;
            }
    return op;
}

////////////////////////////////////// TRATATIVA DA OPÇÃO ESCOLHIDA ///////////////////////////////

int data_do_arquivo (int dia, int mes, int ano)
{

   int ano_bissexto, data_valida = 0;  // USADAS COMO VARIÁVEIS BOOLEANAS
   int data = 0;

   /* Na atribuicao abaixo, se as condicoes forem satisfeitas, a variavel
      recebera' um valor maior do que 0. Esta variavel sera' usada para
      testes booleanos, mais abaixo... */

   ano_bissexto = ( ((ano % 4 == 0) && (ano % 100 > 0)) || (ano % 400 == 0) );

   if (dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12 && ano >= 1900 && ano <= 2100){
    // TODOS OS DADOS NAS FAIXAS VALIDAS?
     if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12){
            data_valida = (dia <= 31); // ESTES MESES TÊM 31 DIAS
        }
    else{
            if (mes == 2) // FEVEREIRO É UM CASO A PARTE...
                {
                    if (ano_bissexto) // SE O ANO FOR BISSEXTO
                        {
                            data_valida = (dia <= 29); // O DIA PODE IR ATÉ 29
                        }else{
                                data_valida = (dia <= 28); // SENÃO SÓ ATÉ 28
                            }
                }else
                {
                        data_valida = (dia <= 30); // SE CHEGOU AQUI É UM MÊS DE 30 DIAS
                    }
            }

        }

   return (data_valida);  // E RETORNAMOS O VALOR; RETORNA 0 SE DATA INVÁLIDA
}

void voltar()
{
    int verif;
    do{

            system("cls");
            textcolor(14);
            printf("\nTem certeza que deseja encerrar? Digite (0)Não e (1)Sim\n");
            textcolor(15);
            printf("\n\tOpção: ");
            scanf("%d", &verif);
            fflush(stdin);

            if((verif <= -1) || (verif >= 2)){
                 textcolor(14);
                 printf("\n\n\t\t\7Opção inválida!! Tente novamente!\n\n\n");
                 textcolor(15);
                 system("pause");
            }

    }while((verif <= -1) || (verif >= 2));
    if(verif == 0)
        {
            system("cls");
            main();

        }else if(verif == 1){
                exit (1);

        }
}

int main(void)
{
        ///////////// HABILITANDO ACENTUAÇÃO ///////////

    setlocale(LC_ALL,"portuguese");

       menu();
}

void func1(float dados[][TAM], char produto[][TAM])
{

    int n = 0;
    int d, m, a, dias = 0;

    do{
        printf("\n  Por favor informe à númeração da estação que deseja carregar: ");
        scanf("%d", &n);
        fflush(stdin);

    }while(n <= 0 || n >= 6);

    while(!dias)
        {

            printf("Entre com dia, mês e ano no formato dd/mm/aaaa: ");
            scanf("%d/%d/%d", &d, &m, &a);
            fflush(stdin);
            dias = data_do_arquivo(d,m,a);

            if (!dias)
                {
                    textcolor(14);
                    printf ("\t\7Data inválida! Tente novamente..\n\n");
                }

        }

    char numEsta[10];
    sprintf(numEsta, "%d", n);
    char data1[5];
    char data2[5];
    char data3[5];
    sprintf(data1,"%d", d);
    sprintf(data2,"%d", m);
    sprintf(data3,"%d", a);

    char nome[100];

    strcpy(nome,"Est_");
    strcat(nome,numEsta);
    strcat(nome,"_");
    strcat(nome,data1);
    strcat(nome,data2);
    strcat(nome,data3);
    strcat(nome,".txt");


    ///////////// ABRINDO ARQUIVO //////////////

    char compon[20];
	float valor1 = 0, valor2 = 0;
	int i = 0;
	FILE *arq;


	arq = fopen(nome, "r");
	if(arq == NULL)
        {
            textcolor(14);
            printf("\n\n\t\7Erro, não foi possível abrir o arquivo\n\n\n");
            textcolor(15);
            system("pause");
            system("cls");
            main();
        }else
            {
                system("cls");
                printf("\tOs Dados Abaixo...\n\n");
                textcolor(15);
                printf("ELEMENTOS QUÍMICOS    QUANTIDADE DE REAGENTE    QUANTIDADE RECICLADA\n\n");

                while(fscanf(arq,"%s%f%f", compon, &valor1, &valor2) != EOF)
                    {
                        //MOVENDO OS DADOS PARA AS MATRIZES GLOBAIS

                        strcpy(produto[i],compon);
                        dados[n][i] = valor1;   //ELEMENTOS DA ESTAÇÃO N, NA POSIÇÃO I
                        dados[n+5][i] = valor2;
                        i++;
                    }

                exibir(dados, produto);
            }
    system("pause");
}

void exibir(float dados[TAM][TAM], char produto[][TAM])
{

    int i;
    for(i = 0; i <= TAM; i++)
        {
            printf("%s\t\t\t\t%.4f\t\t\t%.4f\n",produto[i],dados[1][i],dados[6][i]);



        }
    printf("\n\n\t\t\7...Foram importados do arquivo com sucesso !!! \n \n");
    system("pause");
    system("cls");
    menu();
}

void func2(float dados[][TAM], char produto[][TAM])
{
    system("cls");
    int i;
    int MaiorValor = 0, soma = 0;
    for(i = 0;i <=TAM; i++)
        {
            if(MaiorValor < dados[6][i])
                {
                    MaiorValor = dados[6][i];
                    soma += i;
                }


        }
    printf("\n\nO Principal resíduo produzido é: %s\n\n", produto[soma]);
    system("pause");
    system("cls");
    menu();
}

void func3(float dados[][TAM])
{

    system("cls");

    int i, TotalProduto=0;

    for(i = 0; i <= TAM;i++)
        {
            TotalProduto += dados[6][i];
        }

    printf("\n\nA quantidade Total de Produto Reciclado é: %d\n\n",TotalProduto);
    system("pause");
    system("cls");
    menu();
}

void func4(char produto[][TAM], float dados[TAM][TAM])
{
    char pesquisa[50];
    int i = 0, NaoEncontrado = 0;

    system("cls");
    fflush(stdin);

    printf("Informe o nome do Resíduo desejado: \n");
    gets(pesquisa);
    fflush(stdin);

    for(i = 0; i <= TAM; i++)
        {
            if( (stricmp(pesquisa, produto[i]) ) == 0)
                {
                    printf("\n\tELEMENTO QUÍMICO   QUANTIDADE DE REAGENTE    QUANTIDADE RECICLADA");
                    printf("\n\nPesquisa:  %s\t\t %f\t\t  %f\n\n\n", produto[i], dados[1][i], dados[6][i]);
                    i = TAM;
                    NaoEncontrado = 1;
                }
        }
    if(NaoEncontrado == 0){

            textcolor(14);
            printf("\t\7Resíduo não encontrado!! Verifique se o nome está correto!\n\n\n");
            textcolor(15);
    }
    system("pause");
    system("cls");
    menu();
}

void func5(char produto[][TAM], float dados[TAM][TAM])
{
    int i;
    float eficiencia[TAM];

    system("cls");

    printf("NOME   |||  EFICIENCIA\n\n");
    for(i = 0; i < TAM; i++)
        {
            eficiencia[i] = ((dados[6][i] - dados[1][i]) / dados[6][i]) * 100;
            //CALCULO DE EFICIÊNCIA!! E = (AFLUENTE - EFLUENTE / AFLUENTE) * 100;
            printf("%s ||| %.2f %%\n", produto[i], eficiencia[i]);


        }
        getchar();
        system("cls");
        menu();
}
