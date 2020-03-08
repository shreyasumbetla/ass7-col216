#include<iostream>
#include<cmath>
#include<math.h>
#include<string>
#include <bits/stdc++.h> 
using namespace std; 
int registers[32];

char* mainmem[4096];
int pc;		//program counter
int pcfixed=0; //for branch statements to prevent pc++ in main function

void reverse(char* str){
	char rev[50]="";
	int n1 = strlen(str);
	for(int i=0; i<strlen(str);i++){
		rev[i]=str[n1-i-1];		
	}
strcpy(str,rev);
}

//--------BINARY TO DECIMAL-------------
int bintodec(char* str){

		int dec = 0;
		int m = 1;
		int k=strlen(str)-1;
		printf(" bin form : %s\n", str);
		cout<<"length of bin: "<<strlen(str)<<endl;
		while(k>=0){
			if(str[k]=='1'){
				dec+=m;
			}
			m*=2;
			k--;

		}
	
	
	printf(" dec form : %d\n", dec);
	return dec;

}

//--------BINARY TO DECIMAL SIGNED-------------
int bintodecsigned(char* str){
	int dec = 0;
		if(str[0]=='0'){
			dec = 0;
			int m = 1;
			int k=strlen(str)-1;
			printf(" bin form : %s\n", str);
		cout<<"length of bin: "<<strlen(str)<<endl;
			while(k>=0){
				if(str[k]=='1'){
					dec+=m;
				}
				m*=2;
				k--;

			}
		}
		else{
			dec = 0;
			int m = 1;
			int k=strlen(str)-1;
			printf(" int form : %s\n", str);
		cout<<"length of bin: "<<strlen(str)<<endl;
			while(k>=0){
				if(str[k]=='1'){
					dec+=m;
				}
				m*=2;
				k--;

			}
			cout<<pow(2,strlen(str))<<endl;
			cout<<"dec form neg "<<dec<<endl;
			dec = dec - pow(2,strlen(str));
		}
	
	printf(" dec form : %d\n", dec);
	return dec;

}


//---------SUBSTRING-----------------------
char* substr(char* arr, int begin, int len)
{
    char* res = new char[len];
    for (int i = 0; i < len; i++)
        res[i] = *(arr + begin + i);
    res[len] = 0;
    return res;
}


//-----DECIMAL TO BINARY--------------------
void dectobin(int n,char* str){
int binaryNum=0; 
int neg=0;
    // counter for binary array 
    int i = 0; 
	cout<<"in dec to bin n:"<<n<<endl;
char bin[32]=""; 
if(n<0){
n=n+2147483648;
neg=1;
}
    while (n > 0) { 
  
        // storing remainder in binary array 
	int d = n%2;
	cout<<"d "<<d<<endl;
	if(d==1)
	strcat(bin,"1");
	else
	strcat(bin,"0");
       // binaryNum+= (n % 2); 
	//cout<<binaryNum<<endl;
        n = n / 2; 
        i++; 
	//binaryNum*=10;
    } 
cout<<bin<<endl;
//sprintf(str, "%d", binaryNum);
reverse(bin);
cout<<bin<<endl;

int l = 0;
char bin32[32]="";
cout<<"l "<<strlen(bin)<<endl;

while(l<(32-strlen(bin))){
if(neg==0)
strcat(bin32,"0");
else
strcat(bin32,"1");
l++;
}
strcat(bin32,bin);

strcpy(str,bin32);


cout<<strlen(str)<<endl;
}


//-----DECIMAL TO BINARY--------------------
/*
void dectobin(int n,char* str){
int binaryNum=0; 

    // counter for binary array 
    int i = 0; 
	cout<<"in dec to bin n:"<<n<<endl; 
if(n>=0){
    while (n > 0) { 
  
        // storing remainder in binary array 
	
        binaryNum+= (n % 2); 
	cout<<binaryNum<<endl;
        n = n / 2; 
        i++; 
	binaryNum*=10;
    } 
sprintf(str, "%d", binaryNum);
}
int l = 0;
char bin32[32]="";

while(l<(32-strlen(str))){
strcat(bin32,"0");
l++;
}
strcat(bin32,str);

strcpy(str,bin32);
cout<<strlen(str)<<endl;
}
*/
//---------EXECUTION------------------------
void execute(char* instr){
	char opcode[7];
	printf("in execute\n");
	strncpy( opcode, instr, 6 );
	opcode[6] = '\0';
	printf("opcode %s \n",opcode);
	char rs[6],rt[6],rd[6],shamt[6],offset[16];
	strcpy(rs,substr(instr,6,5));
	strcpy(rt,substr(instr,11,5));
	strcpy(rd,substr(instr,16,5));
	strcpy(shamt,substr(instr,21,5));
	strcpy(offset,substr(instr,16,16));
	cout<<"rs with substr"<<rs<<endl;
	cout<<rs<<" "<<rt<<" "<<rd<<" "<<shamt<<" "<<offset<<endl;
	printf("check %d \n", strcmp(opcode,"000000"));
	printf("length %ld \n", strlen(opcode));
	if(strcmp(opcode,"000000")==0){
		printf("in R type\n");	
		char func[7];
		strncpy(func, instr+26, 6);
		func[6]='\0';
		printf("func %s \n",func);
		if(strcmp(func,"000000")==0){
			printf("sll\n");
			int r1 = bintodec(rs);
			int r2 = bintodec(rt);
			int dest = bintodec(rd);
			int power = bintodecsigned(shamt);
			registers[dest] = registers[r2] * pow(2,power);
			printf("reg %d : %d\n",dest,registers[dest]);
			pcfixed=0;
		//sll
		}
		else if(strcmp(func,"000010")==0){
			printf("srl\n");
			char rs[6],rt[6],rd[6],shamt[6];
			int r1 = bintodec(rs);
			int r2 = bintodec(rt);
			int dest = bintodec(rd);
			int power = bintodecsigned(shamt);
			registers[dest] = registers[r2] / pow(2,power);
			printf("reg %d : %d\n",dest,registers[dest]);
			pcfixed=0;
		printf("srl\n");			
		//srl
		}
		else if(strcmp(func,"100000")==0){
			printf("add\n");
			int r1 = bintodec(rs);
			int r2 = bintodec(rt);
			int dest = bintodec(rd);

			registers[dest] = registers[r2] + registers[r1];
			printf("reg %d : %d\n",dest,registers[dest]);
			pcfixed=0;
		//add
		}
		else if(strcmp(func,"100010")==0){
			printf("sub\n");
			int r1 = bintodec(rs);
			int r2 = bintodec(rt);
			int dest = bintodec(rd);
			registers[dest] = registers[r2] - registers[r1];
			printf("reg %d : %d\n",dest,registers[dest]);
			pcfixed=0;
		//sub
		}
		
	
	}
	else if(strcmp(opcode,"100011")==0){
			printf("lw\n");
			cout<<rs<<"rt"<<rt<<"offset"<<offset<<endl;
			//prettyprint(offset);
			cout<<"after pre "<<offset<<endl;
			char bin[32]="";
			int r1 = bintodec(rs);
			int r2 = bintodec(rt);
			int i = bintodecsigned(offset);
			cout<<"reg r2:"<<mainmem[r1+i]<<r2<<endl;
			int num = bintodec(mainmem[r1+i]);
			cout<<"num "<<num<<endl;
			registers[r2]=num;
			printf("registers %d : %d\n",(r2),registers[r2]);
			pcfixed=0;
		printf("lw\n");

	}
	else if(strcmp(opcode,"101011")==0){
			printf("sw\n");
			cout<<rs<<"rt"<<rt<<"offset"<<offset<<endl;
			char bin[32]="";
			int r1 = bintodec(rs);
			int r2 = bintodec(rt);
			int i = bintodecsigned(offset);
			cout<<"reg r2:"<<registers[r2]<<r2<<endl;
			dectobin(registers[r2],bin);
			cout<<"str bin "<<bin<<" "<<strlen(bin)<<endl;
			//strcpy(mainmem[r1+i],bin);
			mainmem[r1+i]=bin;
			printf("mainmem %d : %s\n",(r1+i),mainmem[r1+i]);
			pcfixed=0;

		printf("sw\n");

	}
	else if(strcmp(opcode,"001000")==0){

			pc = registers[31];
			pcfixed = 1;
			

		printf("jr\n");
	//jr
	}
	else if(strcmp(opcode,"000101")==0){
			int r1 = bintodec(rs);
			int r2 = bintodec(rt);
			int i = bintodecsigned(offset);
			if(r1!=r2){
			pc += i;
			pcfixed=1;
			}
			else{
			pcfixed=0;
			}
		
		printf("bne\n");
	//bne
	}
	else if(strcmp(opcode,"000100")==0){
			int r1 = bintodec(rs);
			int r2 = bintodec(rt);
			int i = bintodecsigned(offset);
			if(r1==r2){
			pc += i;
			pcfixed=1;
			}
			else{
			pcfixed=0;
			}
		
		printf("beq\n");
	//beq
	}
	else if(strcmp(opcode,"000110")==0){
			int r1 = bintodec(rs);
			int i = bintodecsigned(offset);
			if(r1<=0){
			pc += i;
			pcfixed=1;
			}
			else{
			pcfixed=0;
			}
		
		printf("blez\n");
	//blez
	}
	else if(strcmp(opcode,"000111")==0){
			int r1 = bintodec(rs);
			int i = bintodecsigned(offset);
			if(r1>0){
			pc += i;
			pcfixed=1;
			}
			else{
			pcfixed=0;
			}
		
		printf("bgtz\n");
	//bgtz
	}
	else if(strcmp(opcode,"000010")==0){
			char jaddr[26];
			strcpy(jaddr,substr(instr,16,5));
			pc = bintodec(jaddr);
			pcfixed = 1;
			

		printf("j\n");
	//j
	}
	else if(strcmp(opcode,"000011")==0){
			registers[31]=pc+1;
			char jaddr[26];
			strcpy(jaddr,substr(instr,16,5));
			pc = bintodec(jaddr);
			pcfixed = 1;
			

		printf("j\n");
	//jal
	}
}


//----------MAIN FN----------------------------------------
int main(){

char* test[3];
for(int p=0;p<=32;p++){
			registers[p]=0;
			cout<<registers[p]<<endl;
			}
registers[3]=-10;

int i=0;
printf("in main\n");

for(int i=0;i<4096;i++){
	//printf("init %d\n",i);
	mainmem[i] = (char*)malloc(32 * sizeof(char));
	strcpy(mainmem[i],"00000000000000000000000000000000");
}
strcpy(mainmem[0],"00000000001000101111100000000000");
strcpy(mainmem[1],"10101100001000111111111111111111");
strcpy(mainmem[2],"00000000000000000000000000000000");

i=0;
for(int p=0;p<5;p++){
printf(" instr length %ld\n",strlen(mainmem[p]));
printf(" instr %d %s\n",p,mainmem[p]);
}
printf("%d val of i: \n",i);
printf(" instr %d %s\n",i,mainmem[i]);
while(strcmp(mainmem[pc],"00000000000000000000000000000000")){
	printf(" instr %d %s\n",pc,mainmem[pc]);
	execute(mainmem[pc]);
	if(!pcfixed){
	pc++;
	}
}

printf("no of instr : %d\n",pc);
return 0;
}


