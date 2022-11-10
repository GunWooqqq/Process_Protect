#include<stdio.h>
#include<windows.h>
#include<TlHelp32.h>

void Process_Protect();
void Process_Kill();

char buffer[MAX_PATH];

typedef struct Detective{
char pPath[MAX_PATH];
char pName[MAX_PATH];
int exist;
HANDLE hProcess;
PROCESSENTRY32 pe;
HANDLE hSnap;
}pGuard;

int main(int argc, char *argv[])
{
	Process_Protect();
	
	return 0;
}

void Process_Protect()
{
		pGuard De;

		memset(De.pName, 0 ,sizeof(De.pName));
		memset(De.pPath , 0 , sizeof(De.pPath));

		printf("Detective Process Name : ");
		scanf("%s",De.pName);
		printf("Detective Process Full Path : ");
		scanf("%s",De.pPath);
		Process_Kill();	
		while(1){
		De.exist = 0;
		De.pe.dwSize = sizeof(PROCESSENTRY32);
		De.hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
		Process32First(De.hSnap , &De.pe);
			do
			{
				if(!stricmp(De.pe.szExeFile , De.pName)){
					De.exist = 1;
					break;
				}
			}while(Process32Next(De.hSnap,&De.pe));
			if(De.exist != 1){
				MessageBox(NULL,"�ش� ���μ����� ����Ǿ����ϴ� ����� �ϰڽ��ϴ�.","���μ��� ���� Ž��",MB_OK);
				ShellExecute(NULL ,"open",De.pPath ,NULL ,NULL ,SW_SHOW);
			}
			else{
				MessageBox(NULL ,"�ش� ���μ����� ���� �������Դϴ�." ,"���μ��� ������" , MB_OK);
				continue;
			}
		}
}

void Process_Kill()	//Ư�� ���μ��� ���� ���� 
{
	PROCESSENTRY32 pe;
	HANDLE tHandle;
	HANDLE hProcess;
	char buffer[MAX_PATH];
	int pid = 0;

	memset(&pe ,0 ,sizeof(pe));

	pe.dwSize = sizeof(PROCESSENTRY32);

	hProcess =CreateToolhelp32Snapshot(TH32CS_SNAPALL , NULL);

	Process32First(hProcess ,&pe);
	printf("Process Name  :  %s\n", pe.szExeFile);
	printf("Process PID   :  %d\n", pe.th32ProcessID);
	do
	{
		printf("Process Name  :  %s\n\n", pe.szExeFile);
	}while(Process32Next(hProcess , &pe));
	//����ڿ��� ���μ��� �ѹ� �� �����ִ� �뵵 ��ƾ 
	printf("\n\n\n");
	printf("Kill Process Name : ");
	gets(buffer);

	hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPALL , NULL);
	
	Process32First(hProcess , &pe);
	do
	{
		if(!stricmp(buffer, pe.szExeFile))
		{
			tHandle = OpenProcess(PROCESS_ALL_ACCESS , FALSE, pe.th32ProcessID);
			if(TerminateProcess(tHandle , 0))
				printf("Process Exit Success\n");

			else
				printf("Process Exit Fail\n");

			break;
		}
	}while(Process32Next(hProcess , &pe));
}
// 주석 추가 