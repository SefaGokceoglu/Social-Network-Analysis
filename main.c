#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
  
typedef struct CentralityArray
{
	int userid;
	double centrality;
	double central;
}CentralityArray;

struct AdjListNode 
{ 
    int dest; 
    struct AdjListNode* next; 		
}; 

struct AdjList 
{ 
	int nodevalue;
    struct AdjListNode *head;  
}; 


struct Graph 
{ 
    int V; 
    struct AdjList * array; 
}; 
  
void selectionSort(CentralityArray* CA, int n)  
{  
    int i, j, max_index;  
    
    for (i = 0; i < n-1; i++){   
        for (j = i+1; j < n; j++){  
	        if (CA[j].centrality > CA[i].centrality){ 
		        double tmp=CA[j].centrality;
				CA[j].centrality=CA[i].centrality;
				CA[i].centrality=tmp; 
				swap(&CA[j].userid,&CA[i].userid) ;
	  		}
        }  
    }  
}  

struct AdjListNode* newAdjListNode(int dest) 
{ 
    struct AdjListNode* newNode = 
    (struct AdjListNode*) malloc(sizeof(struct AdjListNode)); 
    newNode->dest = dest; 
    newNode->next = NULL; 
    return newNode; 
} 

 
struct Graph* createGraph(int V)
{ 
    struct Graph* graph =  
        (struct Graph*) malloc(sizeof(struct Graph)); 
    graph->V = V; 
  
    graph->array =  
      (struct AdjList*) malloc(V * sizeof(struct AdjList)); 
  
   
    int i; 
    for (i = 0; i < V; ++i) 
        graph->array[i].head = NULL; 
  	
    return graph; 
} 
  

void addEdge(struct Graph* graph, int src, int dest)
{  
	int i=0;
	while(graph->array[i].nodevalue != src){									//src bir kullan�c� idisi bunun arraydaki indexini buluyoruz
		i++;
	}
    struct AdjListNode* newNode = newAdjListNode(dest); 						//yeni bir node olu�turup dest de�erini ald���m�z dest de�i yap�yoruz
    newNode->next = graph->array[i].head; 										//yeni nodenin  nexti arraydeki nodeyi g�steriyor 
    graph->array[i].head = newNode; 											//arraydeki o indexe ise nodeyi yerle�tiyoruz
  	
} 
  

void printGraph(struct Graph* graph)
{ 	
	FILE *file;
	file = fopen("ADJList.txt","a");
    int v;
    for (v = 0; v < graph->V; ++v) 
    { 
    	
        struct AdjListNode* pCrawl = graph->array[v].head;
	    fprintf(file,"\nAdjacency list of vertex %d\n%d ",graph->array[v].nodevalue, graph->array[v].nodevalue); 
        while (pCrawl){ 
            fprintf(file,"-> %d", pCrawl->dest); 
            pCrawl = pCrawl->next; 
        } 
        fprintf(file,"\n"); 
    	}
    	
    printf("\nBUTUN KULLANICLARIN KOMSULARINI GOSTEREN ADJList.txt DOSYASI OLU�TURULDU!!\n");	
} 


void CountEdges(struct Graph* graph , int **mat , int *User ,int lenght)
{ 
    int v;
    int i=0;
    int count;
    for (v = 0; v < lenght; ++v){ 
        struct AdjListNode* pCrawl = graph->array[v].head;
        count=0;
		while (pCrawl){ 
            pCrawl = pCrawl->next; 
            count++;
        }

		mat[i][0] = graph->array[v].nodevalue;
    	mat[i][1] = count;   	
    	i++;	
    } 
}


void CountFollowers(struct Graph* graph , int **mat , int *User ,int lenght)
{
    int v,z,userid;
    
    int i=0;
    int count;
    for(z = 0; z < lenght ; z++){
    	count=0;
	    for(v = 0 ; v <lenght ; v++){ 
	        struct AdjListNode *pCrawl = graph->array[v].head;

	        while (pCrawl){ 
	        	

	        	if(pCrawl->dest == graph->array[z].nodevalue){
	        		count++;
				}
			pCrawl = pCrawl->next;
	        }
		}
	
	    mat[z][0] = graph->array[z].nodevalue;
	    mat[z][1] = count;   
	}
}  


void findUSERS(int *array ,int *len ,char* filename)							//Kullaniclar� sayip kullanici sayisini bulan fonksiyon
{
	int i=0,j=0,founded=0;
	FILE *fp;
	char buff[255];
	fp = fopen(filename, "r");
	fscanf(fp,"%*[^\n]\n");
	while(!feof(fp)){
 		char *arr;
 		fscanf(fp, "%s", buff);
 		arr = strtok(buff,",");
 		j++;
 		founded=0;
 		for(i=0;i<j;i++){
 			if(array[i]==atoi(arr)){
 			founded =1;		
			}
		}
		if(founded==1){
			j--;
		}
		else{
			*len +=1;
			array[i-1]=atoi(arr);
		} 
		while(arr != NULL){
			arr = strtok(NULL, ","); 
        	j++;
        	founded=0;
	 		for(i=0;i<j;i++){
	 			if(array[i]==atoi(arr)){
	 			founded =1;		
				}
			}
			if(founded==1){
				j--;
			}
			else{
				*len +=1;
				array[i-1]=atoi(arr);
			} 
        	arr = strtok(NULL, ",");
		}
 	}
 	fclose(fp);
}

void printMatrix(int **array,int row)									
{
	int i,j;
	for(i=0;i<row;i++){
		for(j=0;j<1;j++){
			printf("\n%d  KULLANICISININ  %d  TANE VAR ",array[i][j],array[i][j+1]);
		
		}
	}
}


void printSubMatrix(int **array,int row, int start)
{
	int i,j;
	for(i=start;i<row;i++){
		for(j=0;j<1;j++){
			
			printf("%d   KULLANICISININ   %d   \n",array[i][j],array[i][j+1]);
		
		}
	}
}


float Ortalama(int **array,int row)
{
	float count=0;
	int i,j;
	for(i=0;i<row;i++){
		for(j=0;j<1;j++){
			count += array[i][j+1];
		
		}
	}
	return count/row ;
}


void swap(int *x , int *y)
{
	int tmp;
	tmp = *x;
	*x = *y;
	*y=tmp;
}

int partition(int **A, int p, int r) 
{
	int x = A[r][1]; //pivot
	int i = p - 1, j;
	for(j = p; j < r ; j++) {
		if(A[j][1] <= x) {
			i = i + 1;
			swap(&A[i][1], &A[j][1]);
			swap(&A[i][0], &A[j][0]); 
		}
	}
	i = i + 1;
	swap(&A[i][1], &A[j][1]);
	swap(&A[i][0], &A[j][0]); 
	return i;
}


void quick_sort(int **A, int p, int r) 
{
	if(p < r) {
		int t = (rand() %( r - p + 1) + p);
		swap(&A[t][1], &A[r][1]);
		swap(&A[t][0], &A[r][0]); 
		
		int q = partition(A, p, r);
		quick_sort(A, p, q - 1);
		quick_sort(A, q + 1, r);
	}
}


void CreateAdjanList(struct Graph* graph, char *filename)				
{
	int lsource=-1,ldestination=-2,source,destination;			//Dosyandan okunan verilere bakarak ADJList olu�turan fonksiyon
	FILE* fp;										
    char buff[255];
 	fp = fopen( filename , "r");
 	fscanf(fp,"%*[^\n]\n");
	while(!feof(fp) && fp){
 		char *array;
 		fscanf(fp, "%d,%d", &source,&destination);			//sourceyi ve destinationu okuyoruz
 		if(lsource != source || ldestination != destination){
 		lsource=source;
 		ldestination=destination;
 		addEdge (graph,source,destination);					// addEdge Fonksiyonu bu  iki parametreyle �a��r�l�yor ve dosya bitene kadar devam ediyor
 		}

 	}
	fclose(fp); 		
}


void printArray(int *array,int len)
{
	int i;
	for(i=0;i<len;i++){
		printf("\n%d . KULLANICI IDSI == %d \n",i,array[i]);
	}
}

struct qnode 
{
	int data;
	struct qnode* next;
};  
typedef struct qnode QNODE;

struct queue
{
    int count;
    QNODE *front;
    QNODE *rear;
};
typedef struct queue QUEUE;

void initialize(QUEUE *q)
{
    q->count = 0;
    q->front = NULL;
    q->rear = NULL;
}

int isempty(QUEUE *q)
{	
	
    return (q->rear == NULL);
}

void enqueue(QUEUE *q, int value)
{
    
        QNODE *tmp;
        tmp = malloc(sizeof(QNODE));
        tmp->data = value;
        tmp->next = NULL;
        if(!isempty(q))
        {
            q->rear->next = tmp;
            q->rear = tmp;
        }
        else
        {
            q->front = q->rear = tmp;
        }
        q->count++;
}

int dequeue(QUEUE *q)
{
    QNODE *tmp;
    int n = q->front->data;
    tmp = q->front;
    q->front = q->front->next;
    q->count--;
    
    if(q->count==0){
    	q->rear=NULL;
    	q->front = NULL;
	}
	else{
		free(tmp);
	}
    return n;
    
    
}
		
void displaypath(int from, int* pred ,int* distance,struct Graph* graph,int foruser)
{	
	FILE *file;
	file = fopen("Yollar.txt","a");										//dijkstra algoritmas� ile bulunan yollar� dosyaya yaz�yor
	int fromindex=0;
	while(from != graph->array[fromindex].nodevalue){					//from ile arrayde tuttu�umuz kullan�c�y� e�itleri arraydeki indexi buluyoruz
		fromindex++;
	}
	if(distance[fromindex]!=9999){										//e�er yol bulunmuyosa ife girmiyo
	
	fprintf(file,"\nFOR USER %d \nDistance == %d \n",foruser,distance[fromindex]);
	
	fprintf(file,"%d <-- ",from);
	while(pred[fromindex]!=0 && pred[fromindex]!=-1){					//pred arrayinde ba�lang�� nodesi 0 yani ba�lang��a var�lmad��� s�rece while giriyor
		fprintf(file,"%d <-- ",pred[fromindex]);
		from=pred[fromindex];											//fromu pred e�erindeki de�er yap�yoruz
		fromindex=0;
		while(from != graph->array[fromindex].nodevalue){				//indexi buluyoruz
		fromindex++;
		}
	}
	fprintf(file,"\n");
	}
	fclose(file);
}

void measure(int from ,int* pred ,int* distance,struct Graph* graph, int foruser, CentralityArray* arr, float* Count, QUEUE* CQ)
{
			int i=0,present;
			int fromindex=0;										//Betweennes Centrality mesasure i�in olan fonksiyon
			while(from != graph->array[fromindex].nodevalue){
				fromindex++;										//fromun arraydeki indexini buluyor	
			}
			if(distance[fromindex] != 9999){						//e�er yol bulunmuyosa ife girmiyo 
			
			
			while(pred[fromindex]!=0 ){
				present=0;											
				while(pred[fromindex] != foruser && pred[fromindex] != arr[i].userid){
					i++;											//ba�lang�� nodesine e�it de�ilse ve pred aray�ndeki de�er ile arraydaki nedeyi e�itliyoruz ve index buluyoruz
				}
				if(pred[fromindex] != foruser){
					
				arr[i].central++;									//Centrality arayinde centali artt�r�yor
				QNODE* tmp =CQ->front;								//Queuey� gezmek i�in bir Qnode olu�turuyor
				while (tmp){
					if(tmp->data == i){
						present=1;									//Queuey� kontrol edip daha �nce bu index varm� diye kontol ediyor varsa present 1 yap�yor
					}
					tmp=tmp->next;
				}
				if(!present){										// present 0 sa 
				enqueue(CQ,i);										//Queue ya hangi nodenin centrali de�i�tiryse o nodenin indexini at�yor
				}
				}
				i=0;
				from=pred[fromindex];								//fromu de�i�tiriyor
				fromindex=0;
				while(from != graph->array[fromindex].nodevalue){
				fromindex++;										//indexini buluyyor
				}
			}
			*Count=*Count +1;										//ba�lang�� nodesi d1 olan kullan�c�n�n ka� tane yolu oldu�unu say�yor
			}
			
			
}

void BFS(struct Graph* graph){ 
	int k;
	for(k=0;k<graph->V;k++){										//b�t�n kullan�clar i�in k�sa yollar� bulmak i�in for
		int startuserid = graph->array[k].nodevalue;
		QUEUE *Q =(QUEUE*) malloc(sizeof(QUEUE));					//qoueue olu�turuyor
		initialize(Q);
		int i=0,parent=0,child=0;
		int* visited = (int*)malloc(graph->V * sizeof(int)); 		//visited ,pred ve distance arrayleri olu�turuyor kullan�c� say�s� kadar 
		int* pred = (int*)malloc(graph->V * sizeof(int)); 
		int* distance = (int*)malloc(graph->V * sizeof(int));
		for (i=0;i<graph->V;i++){
			visited[i]=0;
		}
		for (i=0;i<graph->V;i++){
			pred[i]=-1;
		} 															
		for (i=0;i<graph->V;i++){
			distance[i]=9999;
		}
		int process;
		i =0;
		while(startuserid != graph->array[i].nodevalue){
			i++;													//startuserid'nin arraydeki indexini buluyor
		}
		distance[i]=0;												//distance 0 yap�yor
		enqueue(Q,startuserid);										// kullan�c� idsini queue ya at�yor
		pred[i]=0;													//pred arrayindeki indexi 0 yap�yor
		visited[i]=1;												// visited i�aretliyor
		while(!isempty(Q)){											//queue bo� olana kadar d�n�cek
			process=dequeue(Q);										//process'e kullan� idisni dequeue yap�yor
			parent=0;							
			while(process != graph->array[parent].nodevalue){
			parent++;												//kullan�c� idisiin indexini buluyor
			}
			struct AdjListNode* pCrawl = graph->array[parent].head;// kom�ular�n� gezmek i�in bir node olu�turuyor 
		    while (pCrawl){											//e�er kom�usu varsa giriyor
		    	child=0;											
		    	while(pCrawl->dest != graph->array[child].nodevalue){
				child++;											//kom�usunun indexini buluyor
				}
				if(visited[child] == 0){							//e�er o kum�u gezilmemi�se queueye at�yor 
			    	enqueue(Q,pCrawl->dest); 
			        if(distance[child]>distance[parent]+1){			//distance array�ndeki de�eri parent�n�n distanc� +1 den b�y�kse ife giriyor
			        	distance[child]=distance[parent]+1;			//yeni distanceyi at�yor
						pred[child]=process;						// nerden geldi�ini prede at�yor
						visited[child]=1;							//visited i�aretliyor
					} 
		    	}
		    	pCrawl = pCrawl->next; 								//sonraki kom�usuna ge�iyor
		    }
		}															//en sonunda startuserid i�in gidebilece�i kullan�c�lar i�in en k�sa yollar� buluyo 
	for(i=0;i<graph->V;i++){										//gidebilece�i kullan�c�lar� kontrol etmek i�in for i�inde arrayde d�n�yor		
		int path = graph->array[i].nodevalue;						// de�eri path'e at�yor
		if(path != startuserid)										// e�er path kendisine e�itse ife girmiyo
		displaypath(path,pred,distance,graph,startuserid);			// burda ise displaypath fonksiyonunu �a��r�yor
	}
}																	//ve bunu b�t�n kullan�clar i�in tekrar ediyor 
printf("\nEN KISA YOLLAR Yollar.txt DOSYASINDA !!\n");				
}

void CentralityMeasure(struct Graph* graph , CentralityArray* carray ){ 
	int k,i,parent;																//Bu fonksiyon Centrality �l�mek i�in ve Yukardaki BFS fonksiyonuna benzer algoritmas� benzer
	int startuserid;

	QUEUE *CQ =(QUEUE*) malloc(sizeof(QUEUE));									//meausere fonksiyonunda hangi kullan�c�lar�n arada oldu�unu tutmak i�in bir queue
	initialize(CQ);																		
	for(k=0;k<graph->V;k++){
		float count;
		startuserid = graph->array[k].nodevalue;
		QUEUE *Q =(QUEUE*) malloc(sizeof(QUEUE));
		initialize(Q);
		int i=0,parent=0,child=0;
		int* visited = (int*)malloc(graph->V * sizeof(int)); 
		int* pred = (int*)malloc(graph->V * sizeof(int)); 
		int* distance = (int*)malloc(graph->V * sizeof(int));
		for (i=0;i<graph->V;i++){
			visited[i]=0;
		}
		for (i=0;i<graph->V;i++){
			pred[i]=-1;
		} 															
		for (i=0;i<graph->V;i++){
			distance[i]=9999;
		}
		int process;
		i =0;
		while(startuserid != graph->array[i].nodevalue){
			i++;
		}
		distance[i]=0;
		enqueue(Q,startuserid);
		pred[i]=0;
		visited[i]=1;
		while(!isempty(Q)){	
			process=dequeue(Q);
			parent=0;
			while(process != graph->array[parent].nodevalue){
			parent++;
			}
			struct AdjListNode* pCrawl = graph->array[parent].head;
		    while (pCrawl){
		    	child=0;
		    	while(pCrawl->dest != graph->array[child].nodevalue){
				child++;
				}
				if(visited[child] == 0){
			    	enqueue(Q,pCrawl->dest); 
			        if(distance[child]>distance[parent]+1){
			        	distance[child]=distance[parent]+1;
						pred[child]=process;
						visited[child]=1;
					} 
		    	}
		    	pCrawl = pCrawl->next; 
		    }
		}
		count=0; 													//d1 kullanc�s�n�n ka� tane en k�sa yolu oldu�unu tutmak i�in count'� s�f�rlar�z
		for(i=0;i<graph->V;i++){									// d1 den d1 hari� di�er b�t�n kullan�clar� measure fonksiyonu �a��r�r�z
			int path = graph->array[i].nodevalue;
			if(path != startuserid)
			measure(path,pred,distance,graph,startuserid,carray,&count,CQ);
		}
		int index;
		while(!isempty(CQ)){										//meausre fonksiyonunda queueye hangi kullan�clar�n de�erinin de�i�ti�ini tutan queue bo� olana kadar d�ner
			index=dequeue(CQ);										//hangi kullanc�n�n de�eri de�i�mi�se o kullanc�n�n indexi dequeue ediliyor
			double number =carray[index].central / count;			//central de bizim ka� defa o nodenin yollar aras�nda oldu�unu tutuyoruz countda ise ka� yol oldu�unu 						
			carray[index].central=0;
			carray[index].centrality += number;						//number bu ikisinin b�l�m�n� tutuyoruz ve nodenin centralitysine ekliyoruz

			
			
		}
	}																// b�t�n d1 -- d2 yollar� i�in bu i�lemler ger�ekle�tiriliyor
	selectionSort(carray,graph->V);									//selection sort fonksiyonu ile Centralitynin tutuldu�u struct dizisini s�ral�yopruz
}


int main(){
	int i,j,index;
	int source,destination;
	srand(time(NULL));
	
	
	char filename[40];
    printf("OKUNACAK DOSYANIN ISMINI GIRINIZ :\n");
    scanf("%s",&filename);
    
    int* USERS = (int*)malloc(2000 * sizeof(int));			//KULLANICI IDLERINI TUTAN DIZI
    int size=0;												//KULLANICI SAYISI



    findUSERS(USERS,&size,filename);			// KULLANICI SAYISI VE KULLANICILARI BULUYOR
	
	
    struct Graph* graph = createGraph(size);   //GRAPH OLUSTURMA
    for(i=0;i<size;i++){
    	graph->array[i].nodevalue=USERS[i];
	}
	
	CreateAdjanList(graph, filename);		//ADJ LIST OLUSTURMA

 	 
    //printGraph(graph);				// ADJLIST YAZDIRMA  
	

    int** UC = (int**)malloc(size * sizeof(int*));
	for (index=0;index<size;index++){						// KULLANICI FOLLOW SAYISINI TUTAN MATRIX
	    UC[index] = (int*)malloc(2 * sizeof(int));
	}
	
	
	
	int** UF = (int**)malloc(size * sizeof(int*));
	for (index=0;index<size;index++){					// KULLANICI FOLLOWER SAYISINI TUTAN MATRIX
	    UF[index] = (int*)malloc(2 * sizeof(int));
	}
	
	CentralityArray *CA = (CentralityArray*)malloc(size * sizeof(CentralityArray));
	for(i=0;i<size;i++){
		CA[i].centrality=0;	
		CA[i].central=0;															//Centrality measure de�erini i�in struct array
		CA[i].userid=USERS[i];
	}
	
  	CountEdges(graph, UC, USERS, size );											// FOLLOW say�yor
  	
  	
	CountFollowers(graph, UF, USERS, size );										//FOLLOWER SAYIYOR
	
	
	//printf("\n\n\n\n\n\n**************		UNSORTED MATRIX	FOR FOLLOWS	**************\n\n\n\n\n ");
  	//printMatrix(UC,size);
  	
  	
	//printf("\n\n\n\n\n\n**************		UNSORTED MATRIX	FOR FOLLOWERS	**************\n\n\n\n\n ");  
	//printMatrix(UF,size);

		
	quick_sort(UC, 0, size-1);  												
	quick_sort(UF, 0, size-1);  
	
	//printf("\n\n\n\n\n\n**************		SORTED MATRIX FOR FOLLOWS		**************\n\n\n\n\n ");
	//printMatrix(UC,size);
	
	
	//printf("\n\n\n\n\n\n**************		SORTED MATRIX FOR FOLLOWERS		**************\n\n\n\n\n ");
	//printMatrix(UF,size);
	
	printf("\n**************     EN FAZLA FOLLOWU OLAN 10 KULLANICI         **************\n\n");
  	printSubMatrix(UC,size,size-10);
  	
	  
	printf("\n**************     EN FAZLA FOLLOWER OLAN 10 KULLANICI         **************\n\n");
  	printSubMatrix(UF,size,size-10);
  	
	  
	printf("\n*************		ORTALAMA BAGLANTI SAYILARI 		**************\n\n");
	printf("\nORTALAMA FOLLOW SAYISI = %f\n",Ortalama(UC,size));  
	printf("\nORTALAMA FOLLOWER SAYISI = %f\n",Ortalama(UF,size));    
	  
	
	printf("\n**************		MEDYAN		**************\n ");
  	int n = (size+1) / 2 - 1;
	printf("\nFOLLOW SAYISININ MEDYAN DEGERI = %d\n",UC[n][1]);
	printf("\nFOLLOWER SAYISININ MEDYAN DEGERI = %d\n",UF[n][1]);		 
	
	BFS(graph);															// BUTUN NODELAR ARASI EN KISA YOLU BULAN FONKSIYON

	
	CentralityMeasure(graph,CA);										//BETWEENNESS CENRALITY MEASURE YAPAN FONKS�YON
	
	printf("\n\n************TOP 10 CENTERAL USERS ******************\n");
	
	for(i=0;i<10;i++){
		printf("\n %d KULLANICISININ %.5lf CENTRALITYSI VAR \n",CA[i].userid,CA[i].centrality);
	}
	
	
    return 0;
}
