#include  <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fstream>
#include "forca.h"
using namespace std;
char palavra[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;


int letraexiste(char letra) 
{
  for(int j = 0; j < strlen(palavra); j++) 
  {
    if(letra == palavra[j]) 
    {
      return 1;
    }
  }
  return 0;
}

int chuteserrados() 
{
  int erros = 0;

  for(int i = 0; i < chutesdados; i++) 
  {    
    if(!letraexiste(chutes[i]))
    {
      erros++;
    }
  }
  return erros;
}

int enforcou()
{
  return chuteserrados() >= 5;
}

int ganhou() 
{
  for(int i = 0; i < strlen(palavra); i++) 
  {
    if(!jachutou(palavra[i])) 
    {
      return 0;
    }
  }
  return 1;
}

void abertura() 
{
  cout <<
   "*****************\n"
  "/ Jogo de Forca */\n"
  "*****************\n\n";
}

void chuta() 
{
  char chute;
  cout << "Qual é a letra?(MAIUSCULA)"
  << endl;
  cin >>  chute;
  if(letraexiste(chute)) 
  {
    cout << "Você acertou: a palavra tem a letra " << chute << endl 
    << endl;
  } 
  else 
  {
    cout << "\nVocê errou: a palavra NÃO tem a letra"
    << chute << endl
    << endl;
  } 
  chutes[chutesdados] = chute;
  chutesdados++;
}

int jachutou(char letra) 
{
  int achou = 0;
  for(int j = 0; j < chutesdados; j++) 
  {
    if(chutes[j] == letra) 
    {
      achou = 1;
      break;
    }
  }

  return achou;
}

void desenhaforca() 
{
  int erros = chuteserrados();

  printf("  _______       \n");
  printf(" |/      |      \n");
  printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
  printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
  printf(" |       %c     \n", (erros>=2?'|':' '));
  printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
  printf(" |              \n");
  printf("_|___           \n");
  printf("\n\n");

  for(int i = 0; i < strlen(palavra); i++)
  {
    if(jachutou(palavra[i])) 
    {
      printf("%c ", palavra[i]);
    } 
    else 
    {
      printf("_ ");
    }

  }
  printf("\n");
}

void escolhepalavra() 
{
  FILE* text;

  text = fopen("texto.txt", "r");
  if(text ==  0) 
  {
    cout << "Banco de dados de palavras não disponível\n\n";
    exit(true);
  }

  int qtddepalavras;
  fscanf(text, "%d", &qtddepalavras);

  srand(time(0));
  int randomico = rand() % qtddepalavras;

  for(int i = 0; i <= randomico; i++) 
  {
    fscanf(text, "%s", palavra);
  }
  fclose(text);
}

void adicionapalavra()
{  
   char quer;
   cout <<"\nAdicionar palavra (S/N)? ";
   cin >>  quer;
  // quer = getchar();
  if(quer == 's' || quer == 'S')
  {
    printf("OK...\n");
    char novapalavra[TAMANHO_PALAVRA];
    cout <<"Qual a nova palavra?\n";
    cin >> novapalavra;
        
    //r+ leitura e escrita 
    FILE* text;
    
    text = fopen("texto.txt", "r+");
    if(text == 0)
    {
      cout << "Desculpe, erro";
      exit(1);
    }
    //ler quantidade de palavra
    //no arquivo
    int qtd;
    fscanf(text, "%d", &qtd);
    qtd++; 
    
    //colocando no final do arquivo
    fseek(text,0, SEEK_SET);
    fprintf(text, "%d", qtd);
    
    fseek(text, 0, SEEK_END);
    fprintf(text,"\n%s", novapalavra);
  
    fclose(text);
  }
}

int main() {

  abertura();
  escolhepalavra();

  do 
  {
    desenhaforca();
    chuta();
  }while (!ganhou() && !enforcou());
  
  if(ganhou()) 
  {
    printf("\nParabéns, você ganhou!\n\n");

    printf("       ___________      \n");
    printf("      '._==_==_=_.'     \n");
    printf("      .-\\:      /-.    \n");
    printf("     | (|:.     |) |    \n");
    printf("      '-|:.     |-'     \n");
    printf("        \\::.    /      \n");
    printf("         '::. .'        \n");
    printf("           ) (          \n");
    printf("         _.' '._        \n");
    printf("        '-------'       \n\n");

  }
  else 
  {
    printf("\nPuxa, você foi enforcado!\n");
    printf("A palavra era **%s**\n\n", palavra);

    printf("    _______________         \n");
    printf("   /               \\       \n"); 
    printf("  /                 \\      \n");
    printf("//                   \\/\\  \n");
    printf("\\|   XXXX     XXXX   | /   \n");
    printf(" |   XXXX     XXXX   |/     \n");
    printf(" |   XXX       XXX   |      \n");
    printf(" |                   |      \n");
    printf(" \\__      XXX      __/     \n");
    printf("   |\\     XXX     /|       \n");
    printf("   | |           | |        \n");
    printf("   | I I I I I I I |        \n");
    printf("   |  I I I I I I  |        \n");
    printf("   \\_             _/       \n");
    printf("     \\_         _/         \n");
    printf("       \\_______/           \n");
  }
  adicionapalavra();
}