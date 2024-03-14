#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>
#include "libbmp.c"
#include "libbmp.h"


void bmp_draw_rectangle(bmp_img img, int y_location, 
                    int x_location, int length, int height, u_char color){

    //Unprotected function, you can write pixels after img border

    for(int i = y_location ; i <y_location + height ; i++){
        for(int j = x_location ; j < x_location + length ; j ++){
            bmp_pixel_init(&img.img_pixels[i][j], color, color, color);
        }
    }
    
}
void bmp_img_reset(bmp_img img, int length, int height){

    for(int i = 0 ; i < length ; i++)
    {
        for(int j = 0 ; j < height ; j++)
        {
            bmp_pixel_init(&img.img_pixels[i][j], 255,255,255);
        }
    }

}

int main(int argc, char const *argv[])
{
    int segment_id;
    int* shared_memory = NULL;
    int longueur = atoi(argv[1]), hauteur = atoi(argv[2]);
    int shared_segment_size = 0x6400;
    int histogram[8100], cpt = 0, hist_size = 8100;

    bmp_img img, hist_img;

    /*----------- SHARED MEMORY CONTENT DUMP ------------*/
    
    //Attachment to shared memory segment.
    segment_id = shmget(0x1337, shared_segment_size,IPC_CREAT | 0666);
    if(segment_id == -1){
        perror("shmget()");
        exit(-1);
    }

    shared_memory = (int *)shmat(segment_id, 0, 0);
    if(shared_memory == (int *)-1){
        perror("shmat()");
        exit(-2);
    }
    
    printf("Memoire avec l'id : %d attachee a : %p\n", 
                                segment_id, shared_memory);
    
    
    /*----------- HISTOGRAM CALCULATION --------*/    

    cpt = 0;
    for(int j = 0 ; j < 256 ; j++){
        printf("%d | ", j);
        for (int i = 0; i < hist_size; i++) {
            if (shared_memory[i] == j){
                printf("*");   
                cpt++;
            }
        }
        printf("\n");
        histogram[j] = cpt;
        cpt = 0;
    }
    printf("\n");

    /*----------- IMAGE CREATION ------------*/

    bmp_img_init_df (&img, longueur, hauteur);

    for(int i = 0 ; i < longueur ; i++)
    {
        for(int j = 0 ; j < hauteur ; j++)
        {
            int rand_value = shared_memory[i];
            
            // Fancy image creation
            // Image is actually grayscale
            // But, by playing with a modulo (just for fun),
            // We create a RGB image
            
            bmp_pixel_init(&img.img_pixels[i][j], rand_value,rand_value%100,rand_value%128);
        }
    }

    bmp_img_write(&img, "image.bmp");
    bmp_img_free(&img);

    /*----------- HISTOGRAM CREATION ------------*/
    bmp_img_init_df(&hist_img, 256, 256);

    bmp_img_reset(hist_img, 256,256);

    // Creating bitmap image of histogram :
    // I suppose that the histogram wont be only composed
    // of a unique length*height value
    // As so, The program only draw a 256*256 img

    for(int i = 0; i < 255 ; i++){
        bmp_draw_rectangle(hist_img,i,0,histogram[i],1,histogram[i]*2);
    }
    bmp_img_write(&hist_img, "histogramme.bmp");
    bmp_img_free(&hist_img);
    


    shmdt(shared_memory);   //Detach segment
    shmctl(segment_id, IPC_RMID, 0);//Delete memory segment
    
    return 0;
}