#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

int main() {
		
	//Create the matrix	& initliaze it
	int rows=183, cols=183, i=0, j=0;
	double **mat = (double**)malloc(rows*sizeof(double*));
	for(i=0 ; i<rows ; i++)
		mat[i]=(double*)malloc(cols*sizeof(double));	
	
	
		//Initliaze to zero
		for(i=0 ; i<rows ; i++){
			for(j=0 ; j<cols ; j++){
				mat[i][j]=0;
			}
		}
	
	
	//-------------------------------------------------------------------------------------------------------------//
	
		
		//Open the file and read it into the matrix
		FILE *file;
		file = fopen("matrix.mtx","r");
		if(!file)
			exit(0);
		char *line = NULL;
		int lineCounter=0,r,c;
		double val;
		size_t len=0;
		ssize_t read=0;
	
	//-------------------------------------------------------------------------------------------------------------//
	
	//Read and fill matrix
	while((read = getline(&line,&len,file))!=-1){
		//printf("%s ",line);
		++lineCounter;
		if(lineCounter>2){
			
			char* token = strtok(line," ");	//tokenize string and get the row
			r = atoi(token);
			
			token = strtok(NULL," ");	//tokenize string and get the column
			c = atoi(token);
			
			token = strtok(NULL," ");	//tokenize and get the double value.
			sscanf(token, "%lf", &val);	//Assign to the matrix
			
			
			mat[r-1][c-1] = val;
			
			//printf("%d , %d , %.13f , %.13f\n",r,c,val,mat[r-1][c-1]);
		}
	}
	
	fclose(file);
	
		
	//-------------------------------------------------------------------------------------------------------------//
	
		//Create & Initialize SINE vector
		double* myVec = (double *)malloc(rows*sizeof(double)); //Allocate space for the vector
		if(myVec==NULL){
				printf("\nFailed to allocate space. Running default mode......");
				exit(0);
				//free(myVec);
				//comProd(182);
			}
		for(i=0 ; i<rows ; i++)
			myVec[i]=sin((2*M_PI*i)/182);
        
        
    //-------------------------------------------------------------------------------------------------------------//
        
        
		//Multiply matrices
		double* out = (double *)malloc(rows*sizeof(double)); //Allocate space for the vector
		for(i=0 ; i<rows ; i++)
				out[i]=0;
		for(i=0 ; i<rows ; i++){
			for(j=0 ; j<cols ; j++){
				out[i]+=(mat[i][j]*myVec[j]);
			}
		}
	
	//-------------------------------------------------------------------------------------------------------------//
	
	
		//Compute l2 norm
		double l2=0;
		for(i=0 ; i<rows ; i++){
			l2+=pow(out[i],2);
		}
		l2 = sqrt(l2);
		
		
		//Print Result
		printf("\n%.14f\n\n",l2);
    
	//-------------------------------------------------------------------------------------------------------------//
	
		//Free Matrix
		for(i=0 ; i<rows ; i++){
			free(mat[i]);
		}
		free(mat);
	
	return 0;
}
