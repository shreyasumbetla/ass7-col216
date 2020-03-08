#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
#include <bits/stdc++.h> 

using namespace std;
char* arr[4096];
int registers[32];
int NumOfInstr = 0;





///////////////////////////////////////////////////////////////// SHREYA'S PART /////////////////////////////////////////////////////
char* mainmem[4096];
int pc;		//program counter
int pcfixed=0; //for branch statements to prevent pc++ in main function
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////// execution part //////////////////////////////////////////////////////////

//--------BINARY TO DECIMAL-------------
int bintodec(char* str){
	int dec = 0;
	int m = 1;
	int k=strlen(str)-1;
	printf(" int form : %s\n", str);
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

    	// counter for binary array 
    	int i = 0; 
	cout<<"in dec to bin n:"<<n<<endl; 
    	while (n > 0) { 
  
		// storing remainder in binary array 
		binaryNum+= (n % 2); 
		cout<<binaryNum<<endl;
		n = n / 2; 
		i++; 
		binaryNum*=10;
    	} 

sprintf(str, "%d", binaryNum);
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
			int power = bintodec(shamt);
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
			int power = bintodec(shamt);
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
			int i = bintodec(offset);
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
			int i = bintodec(offset);
			cout<<"reg r2:"<<registers[r2]<<r2<<endl;
			dectobin(registers[r2],bin);
			cout<<"str bin "<<bin<<endl;
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
			int i = bintodec(offset);
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
			int i = bintodec(offset);
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
			int i = bintodec(offset);
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
			int i = bintodec(offset);
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



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void generateBinaryOfInteger(char* str, char* str1);
void generateBinaryOfIntegerBig(char* str, char* str1);
void generateBinaryOfIntegerBigger(char* str, char* str1);
void generateBinaryOfReg(char* str, char* str1);
void parseSpace(char* str, char** parsed);
int decode(char* str);
void proces(char* str);




void initReg(){

	for(int i = 0; i<32;i++)
		registers[i] = 0;


}
//void generateCoe(FILE* poin,);


/////////////////////////////////////////////////////  GENERATE AN INSTRUCTION FROM TOKENS  ///////////////////////////////////////////
void generateInstr(char** parts, char* instr){
	
	//char** parts;
	//parseSpace(str,parts);
	
	if(strcmp(parts[0],"add") == 0){
		
		printf("adding");
		
		char tempDest[10] = "";
		generateBinaryOfReg(parts[1],tempDest);
		
		char tempOp1[10] = "";
		generateBinaryOfReg(parts[2],tempOp1);

		char tempOp2[10] = "";
		generateBinaryOfReg(parts[3],tempOp2);



		strcpy(instr,"000000");
		strcat(instr,tempOp1);
		strcat(instr,tempOp2);
		strcat(instr,tempDest);
		strcat(instr,"00000100000");
	}

	else if(strcmp(parts[0],"sub") == 0){

		printf("subtracting");
		
		char tempDest[10] = "";
		generateBinaryOfReg(parts[1],tempDest);
		
		char tempOp1[10] = "";
		generateBinaryOfReg(parts[2],tempOp1);

		char tempOp2[10] = "";
		generateBinaryOfReg(parts[3],tempOp2);



		strcpy(instr,"000000");
		strcat(instr,tempOp1);
		strcat(instr,tempOp2);
		strcat(instr,tempDest);
		strcat(instr,"00000100010");
	}

	else if(strcmp(parts[0],"sll") == 0){

		printf("sll");
		
		
		char tempDest[10] = "";
		generateBinaryOfReg(parts[1],tempDest);
		
		char tempOp1[10] = "";
		generateBinaryOfReg(parts[2],tempOp1);

		char tempShamt[10] = "";
		generateBinaryOfInteger(parts[3],tempShamt);
		
		

		strcpy(instr,"000000");
		strcat(instr,"00000");
		strcat(instr,tempOp1);
		
		strcat(instr,tempDest);
		strcat(instr,tempShamt);
		strcat(instr,"000000");
	}

	else if(strcmp(parts[0],"srl") == 0){

		printf("srl");
		
		char tempDest[10] = "";
		generateBinaryOfReg(parts[1],tempDest);
		
		char tempOp1[10] = "";
		generateBinaryOfReg(parts[2],tempOp1);

		char tempShamt[10] = "";
		generateBinaryOfInteger(parts[3],tempShamt);
		
		/*
		tempShamt1[5] = "";
		for(int i = 27; i < 32; i++	*/
		
		strcpy(instr,"000000");
		strcat(instr,"000000");
		strcat(instr,tempOp1);
		
		strcat(instr,tempDest);
		strcat(instr,tempShamt);
		strcat(instr,"000010");

	}

	
	else if(strcmp(parts[0],"beq") == 0){printf("beq");
		
		char tempOp1[10] = "";
		generateBinaryOfReg(parts[1],tempOp1);

		char tempOp2[10] = "";
		generateBinaryOfReg(parts[2],tempOp2);

		char tempJ[10] = "";
		generateBinaryOfIntegerBig(parts[3],tempJ);

		strcpy(instr,"000100");
		strcat(instr,tempOp1);
		strcat(instr,tempOp2);
		strcat(instr,tempJ);
		
		
	}

	else if(strcmp(parts[0],"bne") == 0){
		printf("bne");
		char tempOp1[10] = "";
		generateBinaryOfReg(parts[1],tempOp1);

		char tempOp2[10] = "";
		generateBinaryOfReg(parts[2],tempOp2);

		char tempJ[10] = "";
		generateBinaryOfIntegerBig(parts[3],tempJ);

		strcpy(instr,"000101");
		strcat(instr,tempOp1);
		strcat(instr,tempOp2);
		strcat(instr,tempJ);
	}


	else if(strcmp(parts[0],"blez") == 0){
		printf("blez");
		char tempOp1[10] = "";
		generateBinaryOfReg(parts[1],tempOp1);
		/*
		char tempOp2[10] = "";
		generateBinaryOfReg(parts[2],tempOp2);*/

		char tempJ[10] = "";
		generateBinaryOfIntegerBig(parts[2],tempJ);

		strcpy(instr,"000110");
		strcat(instr,tempOp1);
		strcat(instr,"00000");
		strcat(instr,tempJ);
	}


	else if(strcmp(parts[0],"bgtz") == 0){
		printf("bgtz");/*
		char tempOp1[10] = "";
		generateBinaryOfReg(parts[1],tempOp1);

		char tempOp2[10] = "";
		generateBinaryOfReg(parts[2],tempOp2);

		char tempJ[10] = "";
		generateBinaryOfIntegerBig(parts[3],tempJ);

		strcpy(instr,"000101");
		strcat(instr,tempOp1);
		strcat(instr,tempOp2);
		strcat(instr,tempJ);*/



		char tempOp1[10] = "";
		generateBinaryOfReg(parts[1],tempOp1);
		/*
		char tempOp2[10] = "";
		generateBinaryOfReg(parts[2],tempOp2);*/

		char tempJ[10] = "";
		generateBinaryOfIntegerBig(parts[2],tempJ);

		strcpy(instr,"000111");
		strcat(instr,tempOp1);
		strcat(instr,"00000");
		strcat(instr,tempJ);
	}

	else if(strcmp(parts[0],"jal") == 0){printf("jump n link");
		char tempo[10 ] = "";
		//strcpy(tempo,parts[1]);
		
		generateBinaryOfIntegerBigger(parts[1],tempo);
		
		strcpy(instr,"000011");
		strcat(instr,tempo);
	}

	else if(strcmp(parts[0],"j") == 0){printf("jump");
		char tempo[10 ] = "";
		//strcpy(tempo,parts[1]);
		
		generateBinaryOfIntegerBigger(parts[1],tempo);
		
		strcpy(instr,"000010");
		strcat(instr,tempo);
	}

	else if(strcmp(parts[0],"jr") == 0){printf("jump reg");
		char tempo[10] = "";
		generateBinaryOfReg(parts[1],tempo);

		strcpy(instr,"000000");
		strcat(instr,tempo);
		strcat(instr,"000000000000000");
		strcat(instr,"001000");
	}
	
	
	else if(strcmp(parts[0],"lw") == 0){
		printf("load word");
		char tempDest[10] = "";
		generateBinaryOfReg(parts[1],tempDest);

		char tempo[10] = "";
		char offset[10] = "";

		int gf = 0;
		strcpy(tempo,parts[2]);
		for(gf= 0; tempo[gf] != '(';gf++)
			offset[gf] = tempo[gf];
			

		char ba[10] = "";
		for(int gi = gf+1; tempo[gi] != ')'; gi++)
			ba[gi] = tempo[gi];

		char baseadd[10] = "";
		generateBinaryOfReg(ba,baseadd);
		char off[10] = "";
		generateBinaryOfIntegerBig(offset,off);

		strcpy(instr,"100011");
		strcat(instr,baseadd);
		strcat(instr,tempDest);
		
		strcat(instr,off);
		
		
		
	}

	
	else if(strcmp(parts[0],"sw") == 0){


	printf("store word");
		char tempDest[10] = "";
		generateBinaryOfReg(parts[1],tempDest);

		char tempo[10] = "";
		char offset[10] = "";

		int gf = 0;
		strcpy(tempo,parts[2]);
		for(gf= 0; tempo[gf] != '(';gf++)
			offset[gf] = tempo[gf];
			

		char ba[10] = "";
		for(int gi = gf+1; tempo[gi] != ')'; gi++)
			ba[gi] = tempo[gi];

		char baseadd[10] = "";
		generateBinaryOfReg(ba,baseadd);
		char off[10] = "";
		generateBinaryOfIntegerBig(offset,off);

		strcpy(instr,"101011");
		strcat(instr,baseadd);
		strcat(instr,tempDest);
		
		strcat(instr,off);
		
		
	}

	

	arr[NumOfInstr++] = instr;
	printf("%s \n",arr[NumOfInstr-1]);
	//return 0;



}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////// FROM INTEGER IN FORM OF DECIMAL STRING TO BINARY STRING  /////////////////////////////////////////////////////////////////
void generateBinaryOfInteger(char* str, char* str1){
	stringstream geek(str); int x = 0; geek >> x;
	
		int binaryNum[32]; 
  	int n = x; if(x<0) n= n+ 16;
	    // counter for binary array 
	    int i = 0; 
	    while (n > 0) { 
	  
		// storing remainder in binary array 
		binaryNum[i] = n % 2; 
		n = n / 2; 
		i++; 
	    } 
	  
		char str2[5] = "";
	    // printing binary array in reverse order 
	    for (int j = i - 1; j >= 0; j--) 
		str2[j] = (binaryNum[j]) + '0';

		int gh = 5 - strlen(str2);
		for(int gy = 0; gy<gh;gy++) str1[gy] = '0';
		strcat(str1,str2);
		
}





void generateBinaryOfIntegerBig(char* str, char* str1){
	stringstream geek(str); int x = 0; geek >> x;
	
		int binaryNum[32]; 
  	int n = x;
	    // counter for binary array 
		if(x<0) n = n+ 32768;
	    int i = 0; 
	    while (n > 0) { 
	  
		// storing remainder in binary array 
		binaryNum[i] = n % 2; 
		n = n / 2; 
		i++; 
	    } 
	  
		char str2[5] = "";
	    // printing binary array in reverse order 
	    for (int j = i - 1; j >= 0; j--) 
		str2[j] = (binaryNum[j]) + '0';

		int gh = 16 - strlen(str2);
		if(gh !=0){
		for(int gy = 0; gy<gh;gy++) strcat(str1,"0");
		strcat(str1,str2);}

		else strcpy(str1,str2);
		
}



void generateBinaryOfIntegerBigger(char* str, char* str1){
	stringstream geek(str); int x = 0; geek >> x;
	
		int binaryNum[32]; 
  	int n = x; if(x<0) n = n + 2147483648;
	    // counter for binary array 
	    int i = 0; 
	    while (n > 0) { 
	  
		// storing remainder in binary array 
		binaryNum[i] = n % 2; 
		n = n / 2; 
		i++; 
	    } 
	  
		char str2[5] = "";
	    // printing binary array in reverse order 
	    for (int j = i - 1; j >= 0; j--) 
		str2[j] = (binaryNum[j]) + '0';

		int gh = 26 - strlen(str2);
		for(int gy = 0; gy<gh;gy++) str1[gy] = '0';
		strcat(str1,str2);
		
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////// BINARY CODE FOR A REGISTER  ///////////////////////////////////////////////////////////////////////////////
void generateBinaryOfReg(char* str, char* str1){

	if(strcmp(str,"$zero")==0) strcpy(str1,"00000");
	else if(strcmp(str,"$at")==0) strcpy(str1,"00001");
	else if(strcmp(str,"$v0")==0) strcpy(str1,"00010");
	else if(strcmp(str,"$v1")==0) strcpy(str1,"00011");
	else if(strcmp(str,"$a0")==0) strcpy(str1,"00100");
	else if(strcmp(str,"$a1")==0) strcpy(str1,"00101");
	else if(strcmp(str,"$a2")==0) strcpy(str1,"000110");
	else if(strcmp(str,"$a3")==0) strcpy(str1,"00111");
	else if(strcmp(str,"$t0")==0) strcpy(str1,"01000");
	else if(strcmp(str,"$t1")==0) strcpy(str1,"01001");
	else if(strcmp(str,"$t2")==0) strcpy(str1,"01010");
	else if(strcmp(str,"$t3")==0) strcpy(str1,"01011");
	else if(strcmp(str,"$t4")==0) strcpy(str1,"01100");
	else if(strcmp(str,"$t5")==0) strcpy(str1,"01101");
	else if(strcmp(str,"$t6")==0) strcpy(str1,"01110");
	else if(strcmp(str,"$t7")==0) strcpy(str1,"01111");
	else if(strcmp(str,"$s0")==0) strcpy(str1,"10000");
	else if(strcmp(str,"$s1")==0) strcpy(str1,"10001");
	else if(strcmp(str,"$s2")==0) strcpy(str1,"10010");
	else if(strcmp(str,"$s3")==0) strcpy(str1,"10011");
	else if(strcmp(str,"$s4")==0) strcpy(str1,"10100");
	else if(strcmp(str,"$s5")==0) strcpy(str1,"10101");
	else if(strcmp(str,"$s6")==0) strcpy(str1,"10110");
	else if(strcmp(str,"$s7")==0) strcpy(str1,"10111");
	else if(strcmp(str,"$t8")==0) strcpy(str1,"11000");
	else if(strcmp(str,"$t9")==0) strcpy(str1,"11001");
	else if(strcmp(str,"$k0")==0) strcpy(str1,"11010");
	else if(strcmp(str,"$k1")==0) strcpy(str1,"11011");
	else if(strcmp(str,"$gp")==0) strcpy(str1,"11100");
	else if(strcmp(str,"$sp")==0) strcpy(str1,"11101");
	else if(strcmp(str,"$fp")==0) strcpy(str1,"11110");
	else if(strcmp(str,"$ra")==0) strcpy(str1,"11111");

}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
void generateCoe(FILE* poin,char** ){
	
	
	

}
*/



//////////////////////////////////////////////////////// PARSE SPACES AND TOKENISE  /////////////////////////////////////////////////////////////////////////////
void parseSpace(char* str, char** parsed)
{
	int i;

	for (i = 0; i < 100; i++) {
		parsed[i] = strsep(&str, " ");

		if (parsed[i] == NULL)
			break;
		if (strlen(parsed[i]) == 0)
			i--;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////////////// DECODE REGISTERS INTO INTEGER VALUES ///////////////////////////////////////////////////////////////////////
int decode(char* str){

	if(strcmp(str,"$zero")==0) return 0;
	else if(strcmp(str,"$at")==0) return 1;
	else if(strcmp(str,"$v0")==0) return 2;
	else if(strcmp(str,"$v1")==0) return 3;
	else if(strcmp(str,"$a0")==0) return 4;
	else if(strcmp(str,"$a1")==0) return 5;
	else if(strcmp(str,"$a2")==0) return 6;
	else if(strcmp(str,"$a3")==0) return 7;
	else if(strcmp(str,"$t0")==0) return 8;
	else if(strcmp(str,"$t1")==0) return 9;
	else if(strcmp(str,"$t2")==0) return 10;
	else if(strcmp(str,"$t3")==0) return 11;
	else if(strcmp(str,"$t4")==0) return 12;
	else if(strcmp(str,"$t5")==0) return 13;
	else if(strcmp(str,"$t6")==0) return 14;
	else if(strcmp(str,"$t7")==0) return 15;
	else if(strcmp(str,"$s0")==0) return 16;
	else if(strcmp(str,"$s1")==0) return 17;
	else if(strcmp(str,"$s2")==0) return 18;
	else if(strcmp(str,"$s3")==0) return 19;
	else if(strcmp(str,"$s4")==0) return 20;
	else if(strcmp(str,"$s5")==0) return 21;
	else if(strcmp(str,"$s6")==0) return 22;
	else if(strcmp(str,"$s7")==0) return 23;
	else if(strcmp(str,"$t8")==0) return 24;
	else if(strcmp(str,"$t9")==0) return 25;
	else if(strcmp(str,"$k0")==0) return 26;
	else if(strcmp(str,"$k1")==0) return 27;
	else if(strcmp(str,"$gp")==0) return 28;
	else if(strcmp(str,"$sp")==0) return 29;
	else if(strcmp(str,"$fp")==0) return 30;
	else if(strcmp(str,"$ra")==0) return 31;

	else return 32;	




}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////









//////////////////////////////////////////////////////////////////////////////////// PROCESS ONE LINE INSTRUCTION ////////////////////////////////////////////////////////////
void proces(char* str){


	
	char* parts[100];
	parseSpace(str,parts);

	char str1[100] = "";
	generateInstr(parts,str1);


	/*
	if(strcmp(parts[0],"add") == 0){printf("adding");
		int dest = decode(parts[1]);
		int op1 = decode(parts[2]);
		int op2 = decode(parts[3]);
		registers[dest] = registers[op1] + registers[op2];
	}

	else if(strcmp(parts[0],"sub") == 0){printf("subtracting");
		int dest = decode(parts[1]);
		int op1 = decode(parts[2]);
		int op2 = decode(parts[3]);
		registers[dest] = registers[op1] - registers[op2];
	}

	else if(strcmp(parts[0],"sll") == 0){printf("sll");
		
		int dest = decode(parts[1]);
		int op1 = decode(parts[2]);
		//int op2 = strtoi(parts[3]);
		stringstream geek(parts[3]); int x = 0; geek >> x;
		registers[dest] = registers[op1] * pow(2,x);
		//registers(dest) = registers(op1) + registers(op2);
	}

	else if(strcmp(parts[0],"srl") == 0){printf("srl");
		int dest = decode(parts[1]);
		int op1 = decode(parts[2]);
		//int op2 = strtoi(parts[3]);
		stringstream geek(parts[3]); int x = 0; geek >> x;
		registers[dest] = registers[op1] / pow(2,x);
		//registers(dest) = registers(op1) + registers(op2);

	}

	
	else if(strcmp(parts[0],"beq") == 0){printf("beq");
		
	}

	else if(strcmp(parts[0],"bne") == 0){printf("bne");

	}

	else if(strcmp(parts[0],"jal") == 0){printf("jump n link");

	}

	else if(strcmp(parts[0],"j") == 0){printf("jump");

	}

	else if(strcmp(parts[0],"jar") == 0){printf("jump reg");

	}
	
	
	else if(strcmp(parts[0],"lw") == 0){printf("beq");
		
	}

	
	else if(strcmp(parts[0],"sw") == 0){printf("beq");
		
	}

	

	return 0;*/
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





///////////////////////////////////////////////////////////////////// END OF PARSING PART //////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////// START OF EXECUTION PART /////////////////////////////////////////////////////////////////////










/////////////////////////////////////////////////////////////////////////// MAIN ///////////////////////////////////////////////////////////////////////////////////
int main (int agrc, char** argv)
{


	initReg();
	for(int i = 0; i< 32;i++){

		registers[i] = 0;
	}


	FILE* fptr;
	if ((fptr = fopen(argv[1], "r")) == NULL) {
        printf("Error! opening file");
        //Program exits if file pointer returns NULL.
        exit(1);
    	}
	
    	int lineNum = 0;
    	char buffer[1000] = "";
    	while(fgets(buffer,sizeof buffer, fptr) != NULL){
		
    		proces(buffer);
		execute(arr[NumOfInstr-1]);		
	}
		


	//printf("%s\n",arr[NumOfInstr-1]);
	fclose(fptr);
	//fclose(fptr1);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

