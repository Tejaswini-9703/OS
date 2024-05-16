#include <stdio.h>

int main()
{
    int n, f, z, avail;
    printf("enter num of pages: ");
    scanf("%d", &n);
    int ref[n];
    printf("enter ref string: \n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &ref[i]);
    }
    printf("enter num of frames: ");
    scanf("%d", &f);
    int frames[f], used[f], t = 0;
    for (int i = 0; i < f; i++)
    {
        frames[i] = -1;
        used[i] = 0;
    }
    printf("Ref str \tframes/pages \t\t\thit/fault");
    for(int i=0;i<n;i++){
        avail=0;
        printf("\n");
        printf("%d\t",ref[i]);

        for(int j=0;j<f;j++){
            if (frames[j]==-1)
            {
                frames[j]=ref[i];
                used[j]=i;
                avail=1;
                for(int k=0;k<f;k++){
                    printf("\t%d",frames[k]);
                }
                printf("\tF");
                break;
            }           
        }
        if(avail==0){
            for(int j=0;j<f;j++){
                if(frames[j]==ref[i]){
                    used[j]=i;
                    avail=1;
                    for(int k=0;k<f;k++){
                        printf("\t%d",frames[k]);
                    }
                    printf("\tH");
                }
            }
        }

        if(avail==0){
            int min=100, min_index=0;
            for(z=0;z<f;z++){
                if(used[z]<min){
                    min=used[z];
                    min_index=z;
                }
            }
            frames[min_index]=ref[i];
            used[min_index]=i;
            avail=1;
            for(int k=0;k<f;k++){
                printf("\t%d",frames[k]);
            }
            printf("\tF");
        }
    }
    return 0;
}
