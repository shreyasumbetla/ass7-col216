
#include <bits/stdc++.h> 

using namespace std;


vector<string> arr;
vector<int> registers;
int NumOfInstr = 0;
vector<int> delay;
int counter=0;
float ipc=0.0;


///////////////////////////////////////////////////////////////// SHREYA'S PART /////////////////////////////////////////////////////
vector<string> mainmem[4096];
int pc;		//program counter
int pcfixed=0; //for branch statements to prevent pc++ in main function
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////// execution part //////////////////////////////////////////////////////////



void reverse(string& str) 
{ 
    int n = str.length(); 
  
    // Swap character starting from two 
    // corners 
    for (int i = 0; i < n / 2; i++) 
        swap(str[i], str[n - i - 1]); 
} 



//--------BINARY TO DECIMAL-------------
int bintodec(string str){

		int dec = 0;
		int m = 1;
		int k=str.length()-1;
		//printf(" bin form : %s\n", str);
		cout<<" bin form : "<<str<<endl;
		cout<<"length of bin: "<<str.length()<<endl;
		while(k>=0){
			if(str[k] == '1'){
				dec+=m;
			}
			m*=2;
			k--;

		}
	
	
	//printf(" dec form : %d\n", dec);
	cout<<" dec form : "<<dec<<endl;
	return dec;

}

//--------BINARY TO DECIMAL SIGNED-------------
int bintodecsigned(string str){
	int dec = 0;
		if(str.at(0)=='0'){
			dec = 0;
			int m = 1;
			int k=str.length()-1;
			cout<<" bin form : "<<str<<endl;
			cout<<"length of bin: "<<str.length()<<endl;
			while(k>=0){
				if(str.at(k)=='1'){
					dec+=m;
				}
				m*=2;
				k--;

			}
		}
		else{
			dec = 0;
			int m = 1;
			int k=str.length()-1;
			cout<<" int form : "<<str<<endl;
			cout<<"length of bin: "<<str.length()<<endl;
			while(k>=0){
				if(str.at(k)=='1'){
					dec+=m;
				}
				m*=2;
				k--;

			}
			cout<<pow(2,str.length())<<endl;
			cout<<"dec form neg "<<dec<<endl;
			dec = dec - pow(2,str.length());
		}
	
	cout<<" dec form : "<<dec<<endl;

	return dec;

}


//---------SUBSTRING-----------------------
string substr(string& arr, int begin, int len)
{
    string res; //= new char[len];
    for (int i = 0; i < len; i++)
        res.at(i) = arr.at(begin+i);
    res.at(len) = 0;
    return res;
}


//-----DECIMAL TO BINARY--------------------
string dectobin(int n){
	int binaryNum=0; 
	int neg=0;
    	// counter for binary array 
    	int i = 0; 
	cout<<"in dec to bin n:"<<n<<endl;
	string bin; 
	if(n<0){
		n=n+2147483648;
		neg=1;
	}
    	while (n > 0) { 
  
        					// storing remainder in binary array 
		int d = n%2;
		cout<<"d "<<d<<endl;
		if(d==1)
			bin.push_back('1');//strcat(bin,"1");
		else
			bin.push_back('0');//strcat(bin,"0");
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
	string bin32;
	cout<<"l "<<bin.length()<<endl;

	while(l<(32-bin.length())){
		if(neg==0)
			bin32.push_back('0');//strcat(bin32,"0");
		else
			bin32.push_back('1');//strcat(bin32,"1");

		l++;
	}
	bin32 = bin32 + bin;//strcat(bin32,bin);

	//str = bin32;//strcpy(str,bin32);


	cout<<bin32.length()<<endl;
	return bin32;
}


//---------EXECUTION-----------------------

void exeRtype(string instr){
string func = instr.substr(26,6);

int rs = bintodec(instr.substr(6,5));
int rt = bintodec(instr.substr(11,5));
int rd = bintodec(instr.substr(16,5));
cout<<"bintodec:"<<bintodecsigned("11101")<<endl;
	int val = (15 << 26) ;
cout<<"val 15<<26::"<<val<<endl;
int counter = 10;
counter = ((counter&(val))| rd) ;
cout<<"counter :"<<counter<<endl;
if(func == "000000"){
	//sll
	int shamt = bintodecsigned(instr.substr(21,5));
	registers.at(rd) = registers.at(rt)*pow(2,(shamt));
	
}
else if(func == "000010"){
	//srl
	int shamt = bintodecsigned(instr.substr(21,5));
	registers.at(rd) = registers.at(rt)/pow(2,(shamt));

}
else if(func == "100000"){
	//add
	registers.at(rd)=registers.at(rs) + registers.at(rt);

}
else if(func == "100010"){
	//sub
	registers.at(rd)=registers.at(rs) - registers.at(rt);

}
else
	cout<<"Error: wrong func code..."<<endl;
}
 
void exelw(string instr){
	
}

void exesw(string instr){
	int rs = bintodec(instr.substr(6,5));
	int rt = bintodec(instr.substr(11,5));
	int offset = bintodecsigned(instr.substr(16,16));
	arr.at(rs + offset) = dectobin(registers.at(rt));
}

void exejr(string instr){
	pc = registers.at(31);
	pcfixed = 1;

}

void exebne(string instr){
	int rs = bintodec(instr.substr(6,5));
	int rt = bintodec(instr.substr(11,5));
	int offset = bintodecsigned(instr.substr(16,16));
	if(registers.at(rs)!=registers.at(rt)){
		pc+=offset;
		pcfixed = 1;
	}

}

void exebeq(string instr){
int rs = bintodec(instr.substr(6,5));
	int rt = bintodec(instr.substr(11,5));
	int offset = bintodecsigned(instr.substr(16,16));
	if(registers.at(rs)==registers.at(rt)){
		pc+=offset;
		pcfixed = 1;
	}

}

void exeblez(string instr){
	int rs = bintodec(instr.substr(6,5));
	int offset = bintodecsigned(instr.substr(16,16));
	if(registers.at(rs)<=0){
		pc+=offset;
		pcfixed = 1;
	}

}

void exebgtz(string instr){
int rs = bintodec(instr.substr(6,5));
	int offset = bintodecsigned(instr.substr(16,16));
	if(registers.at(rs)>0){
		pc+=offset;
		pcfixed = 1;
	}

}

void exejump(string instr){
int jaddr = bintodec(instr.substr(6,26));
int val = 15<<26;
cout<<"with +"<<(pc&val)+jaddr;
pc = (pc&val)|jaddr;
cout<<"with |"<<pc<<endl;
pcfixed = 1;
}

void exejal(string instr){
int jaddr = bintodec(instr.substr(6,26));
registers.at(31) = (pc+1);
int val = 15<<26;
cout<<"with +"<<(pc&val)+jaddr;
pc = (pc&val)|jaddr;
cout<<"with |"<<pc<<endl;
pcfixed=1;
}

void execute(string instr){
cout<<"opcode"<<instr.substr(0,6)<<endl;
string opcode = instr.substr(0,6);

if(opcode=="000000"){
	exeRtype(instr);
}
else if(opcode=="100011")
	exelw(instr);
else if(opcode=="101011")
	exesw(instr);
else if(opcode=="001000")
	exejr(instr);
else if(opcode=="000101")
	exebne(instr);
else if(opcode=="000100")
	exebeq(instr);
else if(opcode=="000110")
	exeblez(instr);
else if(opcode=="000111")
	exebgtz(instr);
else if(opcode=="000010")
	exejump(instr);
else if(opcode=="000011")
	exejal(instr);
else
	cout<<"Error: wrong opcode..."<<endl;
}

/*
//---------EXECUTION------------------------
void execute(string instr){
	string opcode;
	printf("in execute\n");
	strncpy( opcode, instr, 6 );
	opcode[6] = '\0';
	printf("opcode %s \n",opcode);
	string rs; string rt; string rd; string shamt; string offset;
	strcpy(rs,substr(instr,6,5));
	strcpy(rt,substr(instr,11,5));
	strcpy(rd,substr(instr,16,5));
	strcpy(shamt,substr(instr,21,5));
	strcpy(offset,substr(instr,16,16));
	cout<<"rs with substr"<<rs<<endl;
	cout<<rs<<" "<<rt<<" "<<rd<<" "<<shamt<<" "<<offset<<endl;
	cout<<"check "<< strcmp(opcode,"000000")<<endl;
	cout<<("length "<< strlen(opcode)<<endl;
	if(strcmp(opcode,"000000")==0){
		cout<<"in R type\n";	
		string func;
		strncpy(func, instr+26, 6);
		func.at(6) ='\0';
		cout<<"func "<<func<<endl;
		if(strcmp(func,"000000")==0){
			cout<<"sll"<<endl;
			int r1 = bintodec(rs);
			int r2 = bintodec(rt);
			int dest = bintodec(rd);
			int power = bintodecsigned(shamt);
			registers[dest] = registers[r2] * pow(2,power);
			cout<<"reg "<<dest<<":"<<registers[dest];
			pcfixed=0;
		//sll
		}
		else if(strcmp(func,"000010")==0){
			printf("srl\n");
			string rs;string rt; string rd; string shamt;
			int r1 = bintodec(rs);
			int r2 = bintodec(rt);
			int dest = bintodec(rd);
			int power = bintodecsigned(shamt);
			registers.at(dest) = registers.at(r2) / pow(2,power);
			cout<<"reg  "<<dest<<":"<<registers.at(dest);
			pcfixed=0;
		cout<<"srl"<<endl;			
		//srl
		}
		else if(strcmp(func,"100000")==0){
			cout<<"add";
			int r1 = bintodec(rs);
			int r2 = bintodec(rt);
			int dest = bintodec(rd);

			registers.at(dest) = registers.at(r2) + registers.at(r1);
			cout<<"reg "<<dest<<":"<<registers.at(dest)<<endl;
			pcfixed=0;
		//add
		}
		else if(strcmp(func,"100010")==0){
			cout<<"sub";
			int r1 = bintodec(rs);
			int r2 = bintodec(rt);
			int dest = bintodec(rd);
			registers.at(dest) = registers.at(r2) - registers.at(r1);
			cout<<"reg "<<dest": "<<registers.at(dest)<<endl;
			pcfixed=0;
		//sub
		}
		
	
	}
	else if(strcmp(opcode,"100011")==0){
			cout<<"lw"<<endl;
			cout<<rs<<"rt"<<rt<<"offset"<<offset<<endl;
			//prettyprint(offset);
			cout<<"after pre "<<offset<<endl;
			string bin;
			int r1 = bintodec(rs);
			int r2 = bintodec(rt);
			int i = bintodecsigned(offset);
			cout<<"reg r2:"<<arr.at(r1+i)<<r2<<endl;
			int num = bintodec(arr.at(r1+i));
			cout<<"num "<<num<<endl;
			registers.at(r2)=num;
			cout<<"registers "<<(r2)<<": "<<registers.at(r2)<<endl;
			pcfixed=0;
		//printf("lw\n");
	//lw
	}
	else if(strcmp(opcode,"101011")==0){
			cout<<"sw"<<endl;
			cout<<rs<<"rt"<<rt<<"offset"<<offset<<endl;
			string bin;
			int r1 = bintodec(rs);
			int r2 = bintodec(rt);
			int i = bintodecsigned(offset);
			cout<<"reg r2:"<<registers.at(r2)<<r2<<endl;
			dectobin(registers.at(r2),bin);
			cout<<"str bin "<<bin<<" "<<bin.length()<<endl;
			//strcpy(arr[r1+i],bin);
			arr.at(r1+i)=bin;
			cout<<"arr "<<(r1+i)<<": "<<arr(r1+i)<<endl;
			pcfixed=0;

		//printf("sw\n");
	//sw
	}
	else if(strcmp(opcode,"001000")==0){

			pc = registers[31];
			pcfixed = 1;
			

		cout<<"jr"<<endl;
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
		
		cout<<"bne"<<endl;
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
		
		cout<<"beq"<<endl;
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
		
		cout<<"blez"<<endl;
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
		
		cout<<"bgtz"<<endl;
	//bgtz
	}
	else if(strcmp(opcode,"000010")==0){
			string jaddr;
			strcpy(jaddr,substr(instr,16,5));
			pc = bintodec(jaddr);
			pcfixed = 1;
			

		cout<<"j"<<endl;
	//j
	}
	else if(strcmp(opcode,"000011")==0){
			registers.at(31)=pc+1;
			string jaddr;
			strcpy(jaddr,substr(instr,16,5));
			pc = bintodec(jaddr);
			pcfixed = 1;
			

		cout<<"j"<<endl;
	//jal
	}
}



*/


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void generateBinaryOfInteger(string& str, string& str1);
void generateBinaryOfIntegerBig(string& str, string& str1);
void generateBinaryOfIntegerBigger(string& str, string& str1);
void generateBinaryOfReg(string& str, string& str1);
void parseSpace(string& str, vector<string> parsed);
//int decode(string& str);
void proces(string& str);




void initReg(){

	for(int i = 0; i<32;i++)
		registers.push_back(0);


}



/////////////////////////////////////////////////////  GENERATE AN INSTRUCTION FROM TOKENS  ///////////////////////////////////////////



void generateInstr(vector<string> parts, string& instr,string& finalinstr){
	
	//char** parts;
	//parseSpace(str,parts);
	cout<<"parts.at 0 "<<parts.at(0)<<endl;
	if(parts.at(0)=="add" ){
		
		cout<<"adding"<<endl;
		
		string tempDest;
		generateBinaryOfReg(parts.at(1),tempDest);
		
		string tempOp1;
		generateBinaryOfReg(parts.at(2),tempOp1);

		string tempOp2;
		generateBinaryOfReg(parts.at(3),tempOp2);


		instr = "000000" + tempOp1 + tempOp2 + tempDest + "00000100000";
	
		counter+=delay.at(0);
	}

	else if(parts.at(0)=="sub"){

		cout<<"subtracting"<<endl;
		
		string tempDest;
		generateBinaryOfReg(parts.at(1),tempDest);
		
		string tempOp1;
		generateBinaryOfReg(parts.at(2),tempOp1);

		string tempOp2;
		generateBinaryOfReg(parts.at(3),tempOp2);


		instr = "000000" + tempOp1 + tempOp2 + tempDest + "00000100010";
		
		counter+=delay.at(1);
	}

	else if(parts[0]=="sll" ){

		cout<<"sll"<<endl;
		
		
		string tempDest;
		generateBinaryOfReg(parts.at(1),tempDest);
		
		string tempOp1;
		generateBinaryOfReg(parts.at(2),tempOp1);

		string tempShamt;
		generateBinaryOfInteger(parts.at(3),tempShamt);
		
		
		instr = "00000000000" + tempOp1 + tempDest + tempShamt + "000000";
		
		counter+=delay.at(2);
	}

	else if(parts.at(0)=="srl"){

		cout<<"srl"<<endl;
		
		string tempDest;
		generateBinaryOfReg(parts.at(1),tempDest);
		
		string tempOp1;
		generateBinaryOfReg(parts.at(2),tempOp1);

		string tempShamt;
		generateBinaryOfInteger(parts.at(3),tempShamt);
		
		
		instr = "00000000000" + tempOp1 + tempDest + tempShamt + "000010";
	
		counter+=delay.at(3);

	}

	
	else if(parts.at(0)=="beq"){
	
		cout<<"beq"<<endl;
		
		string tempOp1;
		generateBinaryOfReg(parts.at(1),tempOp1);

		string tempOp2;
		generateBinaryOfReg(parts.at(2),tempOp2);

		string tempJ;
		generateBinaryOfIntegerBig(parts.at(3),tempJ);

		instr = "000100" + tempOp1 + tempOp2 + tempJ;

				counter+=delay.at(4);
		
	}

	else if(parts.at(0)=="bne"){
		cout<<"bne"<<endl;
		string tempOp1;
		generateBinaryOfReg(parts.at(1),tempOp1);

		string tempOp2;
		generateBinaryOfReg(parts.at(2),tempOp2);

		string tempJ;
		generateBinaryOfIntegerBig(parts.at(3),tempJ);

		instr = "000101" + tempOp1 + tempOp2 + tempJ;

		counter+=delay.at(5);
	}


	else if(parts.at(0)=="blez"){
		cout<<"blez"<<endl;
		string tempOp1;
		generateBinaryOfReg(parts[1],tempOp1);
		
		string tempJ;
		generateBinaryOfIntegerBig(parts.at(2),tempJ);

		instr = "000110" + tempOp1 + "00000" + tempJ;


		counter+=delay.at(6);
	}


	else if(parts.at(0)=="bgtz"){
		cout<<"bgtz"<<endl;


	cout<<"parts.at 0 "<<parts.at(0)<<endl;
		string tempOp1;
		generateBinaryOfReg(parts.at(1),tempOp1);
		

		string tempJ;
		generateBinaryOfIntegerBig(parts.at(2),tempJ);

		instr = "000111" + tempOp1 + "00000" + tempJ;

		counter+=delay.at(7);
	}

	else if(parts.at(0)=="jal"){

		printf("jump n link");
		string tempo;
		//strcpy(tempo,parts[1]);
		
		generateBinaryOfIntegerBigger(parts.at(1),tempo);
		
		instr = "000011" + tempo;

		//strcpy(instr,"000011");
		//strcat(instr,tempo);
		counter+=delay.at(8);
	}

	else if(parts.at(0)=="j"){

		printf("jump");
		string tempo;
		//strcpy(tempo,parts[1]);
		
		generateBinaryOfIntegerBigger(parts.at(1),tempo);
		
		instr = "000010" + tempo;
		//strcpy(instr,"000010");
		//strcat(instr,tempo);
		counter+=delay.at(9);
	}

	else if(parts.at(0)=="jr"){

		printf("jump reg");
		string tempo;
		generateBinaryOfReg(parts.at(1),tempo);

		instr = "000000" + tempo + "000000000000000" + "001000";

		
		counter+=delay.at(10);
	}
	
	
	else if(parts.at(0)=="lw"){
		printf("load word");
		string tempDest;
		generateBinaryOfReg(parts.at(1),tempDest);

		string tempo;
		string offset;

		int gf = 0;
		tempo = parts.at(2);
		//strcpy(tempo,parts.at(2));
		for(gf= 0; tempo.at(gf) != '(';gf++)
			offset.push_back(tempo.at(gf));
			

		string ba;
		for(int gi = gf+1; tempo.at(gi) != ')'; gi++)
			ba.push_back(tempo.at(gi));

		string baseadd;
		generateBinaryOfReg(ba,baseadd);
		string off;
		generateBinaryOfIntegerBig(offset,off);

		instr = "100011" + baseadd + tempDest + off;

		
				counter+=delay.at(11);
		
		
	}

	
	else if(parts.at(0)=="sw"){


		printf("store word");
		string tempDest;
		generateBinaryOfReg(parts.at(1),tempDest);

		string tempo;
		string offset;

		int gf = 0;
		tempo = parts.at(2);
		//strcpy(tempo,parts.at(2));
		for(gf= 0; tempo.at(gf) != '(';gf++)
			offset.push_back(tempo.at(gf));
			

		string ba;
		for(int gi = gf+1; tempo.at(gi) != ')'; gi++)
			ba.push_back(tempo.at(gi));

		string baseadd;
		generateBinaryOfReg(ba,baseadd);
		string off;
		generateBinaryOfIntegerBig(offset,off);

		instr = "101011" + baseadd + tempDest + off;

		
		
			counter+=delay.at(12);	
	}
	else{
		cout<<"Error: wrong stmt"<<endl;
	}

	
	
	//arr.push_back(instr);
	arr.at(NumOfInstr)=instr;
	cout<<"num"<<NumOfInstr<<endl;
	cout<<arr.at(NumOfInstr)<<endl;
	cout<<"final"<<instr<<endl;




}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////// FROM INTEGER IN FORM OF DECIMAL STRING TO BINARY STRING  /////////////////////////////////////////////////////////////////
void generateBinaryOfInteger(string& str, string& str1){
	stringstream geek(str); int x = 0; geek >> x;
	
		int binaryNum[32]; 
  	int n = x;
	    // counter for binary array 
	    int i = 0; 
	    while (n > 0) { 
	  
		// storing remainder in binary array 
		binaryNum[i] = n % 2; 
		n = n / 2; 
		i++; 
	    } 
	  
		string str2;
	    // printing binary array in reverse order 
	    for (int j = 0; j <i; j++) 
		str2.push_back((binaryNum[j]) + '0');

	reverse(str2.begin(),str2.end());
		int gh = 5 - str2.length();
		for(int gy = 0; gy<gh;gy++) str1.push_back('0');
		str1 = str1 + str2;
		
}





void generateBinaryOfIntegerBig(string& str, string& str1){
	stringstream geek(str); int x = 0; geek >> x;
	
		int binaryNum[32]; 
  	int n = x;
	    // counter for binary array 
	    int i = 0; 
	    while (n > 0) { 
	  
		// storing remainder in binary array 
		binaryNum[i] = n % 2; 
		n = n / 2; 
		i++; 
	    } 
	  
		string str2;
	    // printing binary array in reverse order 
	    for (int j = 0; j <i; j++) 
		str2.push_back((binaryNum[j]) + '0');

		
	reverse(str2.begin(),str2.end());
		int gh = 16 - str2.length();
		for(int gy = 0; gy<gh;gy++) str1.push_back('0');
		str1 = str1 + str2;
		
}



void generateBinaryOfIntegerBigger(string& str, string& str1){
	stringstream geek(str); int x = 0; geek >> x;
	
		int binaryNum[32]; 
  	int n = x;
	    // counter for binary array 
	    int i = 0; 
	    while (n > 0) { 
	  
		// storing remainder in binary array 
		binaryNum[i] = n % 2; 
		n = n / 2; 
		i++; 
	    } 
	  
		string str2;
	    // printing binary array in reverse order 
	    for (int j = 0; j < i; j++) 
		str2.push_back((binaryNum[j]) + '0');
	reverse(str2.begin(),str2.end());
		int gh = 26 - str2.length();
		for(int gy = 0; gy<gh;gy++) str1.push_back('0');
		str1 = str1 + str2;
		
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////// BINARY CODE FOR A REGISTER  ///////////////////////////////////////////////////////////////////////////////
void generateBinaryOfReg(string& str, string& str1){

	if(str == "$zero") str1 = "00000";
	else if(str == "$at") str1 = "00001";
	else if(str == "$v0") str1 = "00010";
	else if(str == "$v1") str1 = "00011";
	else if(str == "$a0") str1 = "00100";
	else if(str == "$a1") str1 = "00101";
	else if(str == "$a2") str1 = "00110";
	else if(str == "$a3") str1 = "00111";
	else if(str == "$t0") str1 = "01000";
	else if(str == "$t1") str1 = "01001";
	else if(str == "$t2") str1 = "01010";
	else if(str == "$t3") str1 = "01011";
	else if(str == "$t4") str1 = "01100";
	else if(str == "$t5") str1 = "01101";
	else if(str == "$t6") str1 = "01110";
	else if(str == "$t7") str1 = "01111";
	else if(str == "$s0") str1 = "10000";
	else if(str == "$s1") str1 = "10001";
	else if(str == "$s2") str1 = "10010";
	else if(str == "$s3") str1 = "10011";
	else if(str == "$s4") str1 = "10100";
	else if(str == "$s5") str1 = "10101";
	else if(str == "$s6") str1 = "10110";
	else if(str == "$s7") str1 = "10111";
	else if(str == "$t8") str1 = "11000";
	else if(str == "$t9") str1 = "11001";
	else if(str == "$k0") str1 = "11010";
	else if(str == "$k1") str1 = "11011";
	else if(str == "$gp") str1 = "11100";
	else if(str == "$sp") str1 = "11101";
	else if(str == "$fp") str1 = "11110";
	else if(str == "$ra") str1 = "11111";

}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
void generateCoe(FILE* poin,char** ){
	
	
	

}
*/



//////////////////////////////////////////////////////// PARSE SPACES AND TOKENISE  /////////////////////////////////////////////////////////////////////////////
void parseSpace(string& str, vector<string> parsed)
{


	/*
	int i;

	for (i = 0; i < 100; i++) {
		parsed[i] = strsep(&str, " ");

		if (parsed[i] == NULL)
			break;
		if (strlen(parsed[i]) == 0)
			i--;
	}*/


	printf("inside parse");
	stringstream check1(str);


	string intermediate; 
      
    // Tokenizing w.r.t. space ' ' 
    while(getline(check1, intermediate, ' ')) 
    { 
        parsed.push_back(intermediate); 
    } 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////////////// DECODE REGISTERS INTO INTEGER VALUES ///////////////////////////////////////////////////////////////////////
/////////////8888888888888888888888888888888888888888888888
/*
int decode(string str){

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




}*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////









//////////////////////////////////////////////////////////////////////////////////// PROCESS ONE LINE INSTRUCTION ////////////////////////////////////////////////////////////
void proces(vector<string> parts){


	
	//vector<string> parts;
	//parseSpace(str,parts);

	string str1;
	string finalinstr;
	generateInstr(parts,str1,finalinstr);


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

///////////////////////////////////////////////////////////////////// START OF MAIN PART /////////////////////////////////////////////////////////////////////










/////////////////////////////////////////////////////////////////////////// MAIN ///////////////////////////////////////////////////////////////////////////////////
int main (int agrc, char** argv)
{

	
	initReg();

	for(int i=0;i<4096;i++) arr.push_back("00000000000000000000000000000000");



	//////////////////////////////////////// DELAY FILE //////////////////////////////////////////////////////////////////////////////


	
	FILE* fptr2;
	if ((fptr2 = fopen(argv[1], "r")) == NULL) {
        	printf("Error! opening file");
      
        	exit(1);
    	}





    	char buffer2[100] = "";
	

	
    	while(fgets(buffer2,sizeof buffer2, fptr2) != NULL){

		if(strcmp(buffer2,"\n")!=0){
			cout<<"buffer :"<<buffer2<<"done"<<endl;
			string line = buffer2;
			cout<<"line :"<<line<<endl;
			
			string chars = " ";

			vector<string> result;
			
			for (char c: chars) {
			    replace(line.begin(), line.end(), c, ' ');
			}
			 cout<<line<<endl;
			istringstream iss(line);
				for (string s; iss>>s;){
			    		if(s.compare("")!=0){
						result.push_back(s);
						cout<<"s :"<<s<<endl;   
			    		}
			    
				}

			cout<<"result parameters :";
			for(int g = 0; g<2; g++)
			// cout<<result[g]<<" ";
			cout<<result.at(g)<<" ";

			delay.push_back(stoi(result.at(1)));
		cout<<"result added"<<endl;
			//delay.push_back(1);
		}

		
		
		cout<<endl;
		
		
	
	}
	
	for(int i=0;i<12;i++) cout<<delay[i]<<" ";


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	


	////////////////////////// INSTRUCTION FILE ////////////////////////////////////////////////////////////////
	
	FILE* fptr;
	if ((fptr = fopen(argv[2], "r")) == NULL) {
        printf("Error! opening file");
      
        exit(1);
    	}
	
    	int lineNum = 0;

    	char buffer[1000] = "";

	int count=0;

    	while(fgets(buffer,sizeof buffer, fptr) != NULL){
		


		if(strcmp(buffer,"\n")!=0){
			cout<<"buffer :"<<buffer<<"done"<<endl;
			string line = buffer;
			cout<<"line :"<<line<<endl;
			
			string chars = " ";

			vector<string> result;
			
			for (char c: chars) {
			    replace(line.begin(), line.end(), c, ' ');
			}
			 cout<<line<<endl;
			int j =0;
			istringstream iss(line);
				for (string s; iss>>s;){
			    		if(s.compare("")!=0){
						result.push_back(s); j++;   
						cout<<"s :"<<s<<endl;   
			    		}
			    
				}
			
			cout<<"result parameters :";
			cout<<"res 0 "<<result.at(0)<<endl;
			cout<<"res 1 "<<result.at(1)<<endl;
			cout<<"j :"<<j<<endl;
			for(int g = 0; g<j; g++)
			 cout<<result[g]<<" ";

			proces(result);
			cout<<"proces done"<<endl;
			NumOfInstr++;
		}

		
		

	}
	cout<<"\ntotal num of instructions = "<<NumOfInstr<<endl;
	//cout<<" Total number of cycles : "<<counter<<endl;
	//cout<<" IPC : "<<(float)((float)counter/(float)NumOfInstr)<<endl;
	pc=0;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//while(strcmp(arr.at(pc),"00000000000000000000000000000000")!=0){
	cout<<"executing::: " <<arr.at(pc)<<endl;
	while(arr.at(pc)!="00000000000000000000000000000000"){
	cout<<"executing "<<arr.at(pc)<<endl;
	execute(arr.at(pc));
	if(!pcfixed){
		pc++;
		pcfixed = 0;
		}

	}
	/*		
	while(strcmp(arr[pc],"00000000000000000000000000000000")!=0){
		printf(" instr %d %s\n",pc,arr[pc]);
		execute(arr[pc]);
		if(!pcfixed){
		pc++;
		}
	}
	*/

	//printf("%s\n",arr[NumOfInstr-1]);
	//fclose(fptr);
	fclose(fptr2);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


