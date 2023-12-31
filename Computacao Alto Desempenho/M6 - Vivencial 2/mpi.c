// M6 - Vivencial
// Gabriel Hoffmann e Rafael Brustolin
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int ler_arquivo_temps(float **temp_vector, char *nome_arq)
{
    FILE *arq_ref;
    int i, count = 0;
    float *res = (float*) malloc(sizeof(float));
    char line_read[20];
    arq_ref = fopen(nome_arq, "r");
    while(fgets(line_read, 20, arq_ref))
    {
        float aux_val = atof(line_read);
        count++;
        res = (float*) realloc(res, sizeof(float)*count);
        res[count-1] = aux_val;
    }
    fclose(arq_ref);
    *temp_vector = res;
    return count;
}

int main(int argc, char** argv)
{
   char *arquivos_temp[] = {"01.txt", "02.txt", "03.txt", "04.txt", "05.txt", "06.txt", "07.txt", "08.txt", "09.txt", "10.txt", "11.txt", "12.txt"};
   char processor_name[MPI_MAX_PROCESSOR_NAME];
   int name_len, world_size, world_rank, i, value, vector_size, *int_vector;
   float total_child_avg;
   int temps_num = 12;

   MPI_Init(NULL, NULL);
   MPI_Get_processor_name(processor_name, &name_len);
   MPI_Comm_size(MPI_COMM_WORLD, &world_size);
   MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

   int processor_files_len = temps_num / (world_size - 1);
   float avg = 0;

   if (world_rank == 0)
   {
      printf("MASTER: Sending values to children...\n");
      for (i=1; i<world_size; i++)
      {
        int start_index = (i - 1) * processor_files_len;  
        value = start_index;

        MPI_Send(&value, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
      }
   }
   else
   {
      MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      float  *temps;

      int last_index = value + processor_files_len;
  
      for (i=value; i < last_index; i++) {
        int count = ler_arquivo_temps(&temps, arquivos_temp[i]);
        float sum = 0;

        for (int j=0; j<count; j++)
        {
            sum += temps[j];
        }

        float month_avg = sum / count;
        total_child_avg += month_avg;

        printf("CHILD %d, month: %d, month average: %.2f\n", world_rank, i + 1, month_avg);
      }

      printf("CHILD %d Sending data to MASTER...\n", world_rank);
      MPI_Send(&total_child_avg, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
   }

   MPI_Barrier(MPI_COMM_WORLD);

   if (world_rank == 0) {
      float count = 0;
      for (i=1; i<world_size; i++) {
         MPI_Recv(&total_child_avg, 1, MPI_FLOAT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
         count += total_child_avg;
      }
      
      avg = count / 12;
      printf("MASTER: average from temps: %.2f\n", avg);
   }

   MPI_Finalize();
   return 0;
}
