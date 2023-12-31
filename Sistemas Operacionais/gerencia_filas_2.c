/*
 *  * Este programa simula a criação de processos e mostra como o bloco descritor é utilizado 
 *   * para "migrar" esses processos entre as filas do sistema.
 *    *
 *     * Este programa foi criado apenas para fins didáticos, pois abstrai detalhes implementados 
 *      * por um SO real para gerenciar a execução de processos durante seu ciclo de vida.
 *       */

#include <stdio.h>

void cria_processo();
void define_info();

#define MAX_PROCESS 10 /* Quantidade máxima de processos que o sistema suporta */

typedef struct DescProc {
	    char     estado_atual;
	        int      prioridade;
		    unsigned inicio_memoria;
		        unsigned tamanho_memoria;
			    unsigned tempo_cpu;
			        unsigned proc_pc;
				    unsigned proc_sp;
				        unsigned proc_acc;
					    unsigned proc_rx;
					        struct   DescProc *proximo;
} DescProc;

typedef struct DescProcLista {
	    DescProc* primeiro;
	        DescProc* ultimo;
} DescProcLista;


DescProc tab_desc[MAX_PROCESS]; /* Quantidade máxima permitida de processos criados no sistema */
DescProcLista desc_livre;
DescProcLista espera_cpu;
DescProcLista usando_cpu;
DescProcLista bloqueados;

int main() {
	    int i;

	        printf("Organizando a estrutura de descritores disponiveis no sistema operacional.\n");
		    for(i = 0; i < MAX_PROCESS - 1; i++)
			            tab_desc[i].proximo = &tab_desc[i + 1];


		        tab_desc[i].proximo = NULL;
			    printf("Organizando a fila desc_livres para uso dos processos.\n");
			        desc_livre.primeiro = &tab_desc[0];
				    desc_livre.ultimo = &tab_desc[MAX_PROCESS - 1];

				        printf("Inicializando as filas: espera_cpu, usando_cpu e bloqueados.\n");
					    espera_cpu.primeiro = NULL;
					        espera_cpu.ultimo   = NULL;
						    usando_cpu.primeiro = NULL;
						        usando_cpu.ultimo   = NULL;
							    bloqueados.primeiro = NULL;
							        bloqueados.ultimo   = NULL;
								    
								    printf("Criando os processos...\n");
								        for(i = 0; i < MAX_PROCESS - 1; i++)
										        cria_processo();
									    
									    printf("Done!\n");
									        return 0;
}

void cria_processo() {
	    DescProc* processo = desc_livre.primeiro;
	        printf("Definindo informacoes do processo (PCB)\n");
		    define_info(processo);
		        printf("Atualizando a fila desc_livre... O processo em execucao esta usando um dos descritores.\n");
			    DescProc* proximo_livre = desc_livre.primeiro->proximo;
			        desc_livre.primeiro = proximo_livre;
				    printf("Processo criado... migramos ele para a fila espera_cpu.\n");
				        if(espera_cpu.primeiro == NULL) {
						        espera_cpu.primeiro = espera_cpu.ultimo = processo;
							    } else {
								            espera_cpu.ultimo->proximo = processo;
									            espera_cpu.ultimo = processo;
										            processo->proximo = NULL;
											        }
}

void define_info(DescProc* processo) { /* cria o processo inserindo informações em seu PCB */
	    printf("Voce define aqui as informacoes... :-)\n");
	        /* Definir os dados do processo aqui */
}

