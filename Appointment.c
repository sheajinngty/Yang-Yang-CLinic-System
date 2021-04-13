#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<Windows.h>
#pragma warning(disable:4996)
SYSTEMTIME t;

typedef struct {
	int hrs, min;
}Time;

typedef struct {
	int day, month, year;
}Date;

typedef struct {
	Date todayDate;
	char ptID[6], ptName[40], gender;
	char nrsName[40], drName[40];
	Time fromTime, toTime;
	char week[10];
	Date appmtDate;
	char remark[40];
}Appointment;

Date date;
Time fromTime, toTime;
Appointment appointment, modTrack[20], delTrack[20], addTrack[20], appmt[20] = { { 27,12,2018,"P0001","Amy",'F',"Lisa","Isabell",14,00,16,00,"Sunday",30,12,2018,"Chest Pain" }
,{ 14,12,2018,"P0004","Dan",'M',"Ken","Nike",10,30,12,30,"Friday",21,12,2018,"Headache" },{ 16,12,2018,"P0006","Fred",'M',"Mike","Jack",13,00,15,00,"Saturday",22,12,2018,"Vomit" }
,{ 21,12,2018,"P0002","Ben",'M',"Mike","Ken",11,00,13,00,"Monday",31,12,2018,"Cough" },{ 22,12,2018,"P0003","Calista",'F',"Mike","Ken",9,00,11,00,"Wednesday",2,1,2019,"Cold" }
,{ 22,12,2018,"P0005","Emily",'F',"Lisa","Isabell",14,30,16,30,"Tuesday",1,1,2019,"Asthma" },{ 20,12,2018,"P0001","Amy",'F',"Nike","Jack",15,00,17,00,"Friday",28,12,2018,"Fever" }
,{ 29,12,2018,"P0007","Grace",'F',"Nike","Jack",13,30,15,30,"Saturday",5,1,2019,"Heart Pain" },{ 27,12,2018,"P0008","Henry",'M',"Mike","Ken",17,00,19,00,"Monday",7,1,2019,"Flu" }
,{ 1,1,2019,"P0010","Jayden",'M',"Lisa","Isabell",18,00,20,00,"Tuesday",8,1,2019,"Dizzy" } };

//void patientRecord();

void displaySchedule();
void findSchedule(int*);
void addAppointment(int*);
void modifyAppointment(int*);
void deleteAppointment(int*);
void trackReport(int, int, int, int);
void appointmentModule();

void allMenus(int);
void errorMessage();
int genderValidate();
void patientIdDataValidate(char patientId[]);

void appointmentModule()
{
	
	/*patientRecord();*/
	
	int decision, appmtMod = 0, appmtDel = 0, appmtAdd = 0, appmtFd = 0;

	do
	{
		allMenus(5);

		printf(" Please enter your option : ");
		scanf("%d", &decision);
		printf("\n");
		while (decision < 1 || decision > 7)
		{
			errorMessage();
			rewind(stdin);
			scanf("%d", &decision);
			printf("\n");
		}

		if (decision == 1)
			displaySchedule();
		else if (decision == 2)
			findSchedule(&appmtFd);
		else if (decision == 3)
			addAppointment(&appmtAdd);
		else if (decision == 4)
			modifyAppointment(&appmtMod);
		else if (decision == 5)
			deleteAppointment(&appmtDel);
		else if (decision == 6)
			trackReport(appmtMod, appmtDel, appmtAdd, appmtFd);
		else if (decision == 7)
			return;
	} while (decision != 7);

	system("pause");
}

//void patientRecord()
//{
//	FILE *AppmtDetailBin, *AppmtDetailBackupBin;
//	AppmtDetailBin = fopen("appointmentRecord.bin", "wb");
//	AppmtDetailBackupBin = fopen("appmtBackupRecord.bin", "wb");
//
//	fwrite(&appmt, sizeof(appmt), 1, AppmtDetailBin);
//	fwrite(&appmt, sizeof(appmt), 1, AppmtDetailBackupBin);
//
//	fclose(AppmtDetailBin);
//	fclose(AppmtDetailBackupBin);
//}

void displaySchedule()
{
	FILE *DisplayBin;
	DisplayBin = fopen("appointmentRecord.bin", "rb");

	int appmtRecord = 0, i = 0, j = 0, count = 0;

	printf("\n");
	printf(" Appointment   Patient Detail                 Nurse On Duty   Doctor Preferred   Time                                                            \n");
	printf(" Added Date    ID       Name         Gender   Name            Name               From     To       Week         Date         Remark              \n");
	printf(" ===========   ======   ==========   ======   =============   ================   ======   ======   ==========   ==========   ====================\n");

	while (fread(&appointment, sizeof(appointment), 1, DisplayBin) != 0)
	{
		if (appointment.gender != '\0')
		{
			appmt[i] = appointment;
			appmtRecord++;
			i++;
		}
	}
	for (i = 0; i < appmtRecord; i++)
	{
		for (j = 0; j < appmtRecord; j++)
		{
			if (appmt[i].appmtDate.year == appmt[j].appmtDate.year)
			{
				if (appmt[i].appmtDate.month == appmt[j].appmtDate.month)
				{
					if (appmt[i].appmtDate.day == appmt[j].appmtDate.day)
					{
						if (appmt[i].fromTime.hrs == appmt[j].fromTime.hrs)
						{
							if (appmt[i].fromTime.min < appmt[j].fromTime.min)
							{
								appointment = appmt[j];
								appmt[j] = appmt[i];
								appmt[i] = appointment;
							}
						}
						else if (appmt[i].fromTime.hrs < appmt[j].fromTime.hrs)
						{
							appointment = appmt[j];
							appmt[j] = appmt[i];
							appmt[i] = appointment;
						}
					}
					else if (appmt[i].appmtDate.day < appmt[j].appmtDate.day)
					{
						appointment = appmt[j];
						appmt[j] = appmt[i];
						appmt[i] = appointment;
					}
				}
				else if (appmt[i].appmtDate.month < appmt[j].appmtDate.month)
				{
					appointment = appmt[j];
					appmt[j] = appmt[i];
					appmt[i] = appointment;
				}
			}
			else if (appmt[i].appmtDate.year < appmt[j].appmtDate.year)
			{
				appointment = appmt[j];
				appmt[j] = appmt[i];
				appmt[i] = appointment;
			}
		}
	}
	for (i = 0; i < appmtRecord; i++)
	{
		printf(" %2d-%2d-%2d    %-6s   %-10s   %-6c   %-13s   %-16s   %02d:%02d    %02d:%02d    %-10s   %2d-%2d-%2d   %-20s\n", appmt[i].todayDate, appmt[i].ptID, appmt[i].ptName,
			appmt[i].gender, appmt[i].nrsName, appmt[i].drName, appmt[i].fromTime, appmt[i].toTime, appmt[i].week, appmt[i].appmtDate, appmt[i].remark);
	}

	printf(" < %d Schedule Listed >\n\n", appmtRecord);
	fclose(DisplayBin);
}
void findSchedule(int*appmtFd)
{
	FILE *fReadBin;
	fReadBin = fopen("appointmentRecord.bin", "rb");
	int i = 0, count = 0;

	while (fread(&appointment, sizeof(appointment), 1, fReadBin) != 0)
	{
		if (appointment.gender != '\0')
		{
			appmt[i] = appointment;
			count++;
			i++;
		}
	}
	fclose(fReadBin);

	FILE *FindBin;
	FindBin = fopen("appointmentRecord.bin", "wb");

	int totalFind = 0, get;
	char sure, choose;

	printf("\n");
	do
	{
		printf(" Find Appointment?(Y=Yes,N=No): ");
		rewind(stdin);
		scanf("%c", &choose);
	} while (toupper(choose) != 'Y' && toupper(choose) != 'N');

	while (toupper(choose) == 'Y')
	{
		get = 0;
		printf("\n Search >>\n");
		printf(" Patient ID: ");
		rewind(stdin);
		scanf("%[^\n]", &appointment.ptID);
		printf(" Appointment Date (day-month-year) : ");
		rewind(stdin);
		scanf("%d-%d-%d", &appointment.appmtDate.day, &appointment.appmtDate.month, &appointment.appmtDate.year);
		printf(" Appointment Time (hrs:time)       : ");
		rewind(stdin);
		scanf("%d:%d", &appointment.fromTime.hrs, &appointment.fromTime.min);

		for (i = 0; i < count; i++)
		{
			if (strcmp(appmt[i].ptID, appointment.ptID) == 0 && appmt[i].appmtDate.day == appointment.appmtDate.day && appmt[i].appmtDate.month == appointment.appmtDate.month
				&& appmt[i].appmtDate.year == appointment.appmtDate.year && appmt[i].fromTime.hrs == appointment.fromTime.hrs && appmt[i].fromTime.min == appointment.fromTime.min)
			{
				printf(" %2d-%2d-%2d    %-6s   %-10s   %-6c   %-13s   %-16s   %02d:%02d    %02d:%02d    %-10s   %2d-%2d-%2d   %-20s\n", appmt[i].todayDate, appmt[i].ptID, appmt[i].ptName,
					appmt[i].gender, appmt[i].nrsName, appmt[i].drName, appmt[i].fromTime, appmt[i].toTime, appmt[i].week, appmt[i].appmtDate, appmt[i].remark);
				get = 1;
				totalFind++;
			}
		}
		if (get == 0)
			printf("\n Undefined appointment record....\n");

		do
		{
			printf("\n Any appointment to find? (Y=Yes,N=No): ");
			rewind(stdin);
			scanf("%c", &choose);
		} while (toupper(choose) != 'Y' && toupper(choose) != 'N');
	}

	*appmtFd = totalFind;
	fwrite(&appmt, sizeof(appmt), 1, FindBin);
	printf(" Total %d appointment finding process have been successfully done\n\n", totalFind);

	fclose(FindBin);
}
void addAppointment(int*appmtAdd)
{
	FILE *aReadBin;
	aReadBin = fopen("appointmentRecord.bin", "rb");
	int i = 0, count = 0;

	while (fread(&appointment, sizeof(appointment), 1, aReadBin) != 0)
	{
		if (appointment.gender != '\0')
		{
			appmt[i] = appointment;
			count++;
			i++;
		}
	}
	fclose(aReadBin);

	FILE *addbin;
	addbin = fopen("appointmentRecord.bin", "ab");
	GetLocalTime(&t);

	int totalAdd = 0;
	char sure, choose;

	do
	{
		printf("\n Add Appointment? (Y=Yes,N=No) ");
		rewind(stdin);
		scanf("%c", &choose);
	} while (toupper(choose) != 'Y' && toupper(choose) != 'N');

	while (toupper(choose) == 'Y')
	{
		printf(" Patient ID                                : ");
		rewind(stdin);
		scanf("%[^\n]", &appointment.ptID);
		patientIdDataValidate(appointment.ptID);

		printf(" Patient Name                              : ");
		rewind(stdin);
		scanf("%[^\n]", &appointment.ptName);

		do {
			printf(" Patient Gender                            : ");
			rewind(stdin);
			scanf("%c", &appointment.gender);
			i = genderValidate(appointment.gender);
		} while (i == 1);

		printf(" Nurse on Duty                             : ");
		rewind(stdin);
		scanf("%[^\n]", &appointment.nrsName);
		printf(" Doctor Preferred                          : ");
		rewind(stdin);
		scanf("%[^\n]", &appointment.drName);
		printf(" Appointment Time (hrs:time)               : ");
		rewind(stdin);
		scanf("%d:%d", &appointment.fromTime.hrs, &appointment.fromTime.min);
		printf(" Appointment Week                          : ");
		rewind(stdin);
		scanf("%[^\n]", &appointment.week);
		printf(" Appointment Date (day-month-year)         : ");
		rewind(stdin);
		scanf("%d-%d-%d", &appointment.appmtDate.day, &appointment.appmtDate.month, &appointment.appmtDate.year);
		printf(" Patient Remark                            : ");
		rewind(stdin);
		scanf("%[^\n]", &appointment.remark);

		appointment.toTime.hrs = appointment.fromTime.hrs + 2;
		appointment.toTime.min = appointment.fromTime.min;
		appointment.todayDate.day = t.wDay;
		appointment.todayDate.month = t.wMonth;
		appointment.todayDate.year = t.wYear;
	
		printf(" %2d-%2d-%2d    %-6s   %-10s   %-6c   %-13s   %-16s   %02d:%02d    %02d:%02d    %-10s   %2d-%2d-%2d   %-20s\n", appointment.todayDate, appointment.ptID, appointment.ptName,
			appointment.gender, appointment.nrsName, appointment.drName, appointment.fromTime, appointment.toTime, appointment.week, appointment.appmtDate, appointment.remark);

		printf(" Sure to add appointment? (Y=Yes,N=No) ");
		rewind(stdin);
		scanf("%c", &sure);

		if (toupper(sure) == 'Y')
		{
			addTrack[totalAdd] = appointment;
			fwrite(&appointment, sizeof(appointment), 1, addbin);
			totalAdd++;
			printf(" Appointment has been successfully added...\n");
		}
		else
			printf(" Appointment fail to add on\n");

		do
		{
			printf("\n Any More Appointment? (Y=Yes,N=No) ");
			rewind(stdin);
			scanf("%c", &choose);
		} while (toupper(choose) != 'Y' && toupper(choose) != 'N');
	}
	*appmtAdd = totalAdd;
	printf(" Total %d appointment records have been successfully added.....\n\n", totalAdd);

	fclose(addbin);
}
void modifyAppointment(int*appmtMod)
{
	FILE *mReadBin;
	mReadBin = fopen("appointmentRecord.bin", "rb");
	int i = 0, count = 0, a;

	while (fread(&appointment, sizeof(appointment), 1, mReadBin) != 0)
	{
		if (appointment.gender != '\0')
		{
			appmt[i] = appointment;
			count++;
			i++;
		}
	}
	fclose(mReadBin);

	FILE *ModifyBin;
	ModifyBin = fopen("appointmentRecord.bin", "wb");

	int totalModify = 0, get;
	char sure, choose;

	do
	{
		printf("\n Modify Appointment?(Y=Yes,N=No): ");
		rewind(stdin);
		scanf("%c", &choose);
	} while (toupper(choose) != 'Y' && toupper(choose) != 'N');

	while (toupper(choose) == 'Y')
	{
		get = 0;
		printf("\n Search >>\n");
		printf(" Patient ID: ");
		rewind(stdin);
		scanf("%[^\n]", &appointment.ptID);
		printf(" Appointment Date (day-month-year) : ");
		rewind(stdin);
		scanf("%d-%d-%d", &appointment.appmtDate.day, &appointment.appmtDate.month, &appointment.appmtDate.year);
		printf(" Appointment Time (hrs:time)       : ");
		rewind(stdin);
		scanf("%d:%d", &appointment.fromTime.hrs, &appointment.fromTime.min);

		for (i = 0; i < count; i++)
		{
			if (strcmp(appmt[i].ptID, appointment.ptID) == 0 && appmt[i].appmtDate.day == appointment.appmtDate.day && appmt[i].appmtDate.month == appointment.appmtDate.month
				&& appmt[i].appmtDate.year == appointment.appmtDate.year && appmt[i].fromTime.hrs == appointment.fromTime.hrs && appmt[i].fromTime.min == appointment.fromTime.min)
			{
				printf(" %2d-%2d-%2d    %-6s   %-10s   %-6c   %-13s   %-16s   %02d:%02d    %02d:%02d    %-10s   %2d-%2d-%2d   %-20s\n", appmt[i].todayDate, appmt[i].ptID, appmt[i].ptName,
					appmt[i].gender, appmt[i].nrsName, appmt[i].drName, appmt[i].fromTime, appmt[i].toTime, appmt[i].week, appmt[i].appmtDate, appmt[i].remark);

				printf(" Patient ID                                : ");
				rewind(stdin);
				scanf("%[^\n]", &appointment.ptID);
				patientIdDataValidate(appointment.ptID);

				printf(" Patient Name                              : ");
				rewind(stdin);
				scanf("%[^\n]", &appointment.ptName);

				do {
					printf(" Patient Gender                            : ");
					rewind(stdin);
					scanf("%c", &appointment.gender);
					a = genderValidate(appointment.gender);
				} while (a == 1);

				printf(" Nurse on Duty                             : ");
				rewind(stdin);
				scanf("%[^\n]", &appointment.nrsName);
				printf(" Doctor Preferred                          : ");
				rewind(stdin);
				scanf("%[^\n]", &appointment.drName);
				printf(" Appointment Time (hrs:time)               : ");
				rewind(stdin);
				scanf("%d:%d", &appointment.fromTime.hrs, &appointment.fromTime.min);
				printf(" Appointment Week                          : ");
				rewind(stdin);
				scanf("%[^\n]", &appointment.week);
				printf(" Appointment Date (day-month-year)         : ");
				rewind(stdin);
				scanf("%d-%d-%d", &appointment.appmtDate.day, &appointment.appmtDate.month, &appointment.appmtDate.year);
				printf(" Patient Remark                            : ");
				rewind(stdin);
				scanf("%[^\n]", &appointment.remark);

				appointment.toTime.hrs = appointment.fromTime.hrs + 2;
				appointment.toTime.min = appointment.fromTime.min;
				appointment.todayDate.day = t.wDay;
				appointment.todayDate.month = t.wMonth;
				appointment.todayDate.year = t.wYear;

				printf(" Sure to modify ? ");
				rewind(stdin);
				scanf("%c", &sure);

				if (toupper(sure) == 'Y')
				{
					modTrack[totalModify] = appointment;
					appmt[i].todayDate = appointment.todayDate;
					strcpy(appmt[i].ptID, appointment.ptID);
					strcpy(appmt[i].ptName, appointment.ptName);
					appmt[i].gender = appointment.gender;
					strcpy(appmt[i].nrsName, appointment.nrsName);
					strcpy(appmt[i].drName, appointment.drName);
					appmt[i].fromTime = appointment.fromTime;
					appmt[i].toTime = appointment.toTime;
					strcpy(appmt[i].week, appointment.week);
					appmt[i].appmtDate = appointment.appmtDate;
					strcpy(appmt[i].remark, appointment.remark);
					totalModify++;
				}
				else
					printf(" Data modify rejected....\n");
				get = 1;
			}
		}
		if (get == 0)
			printf("\n Undefined appointment record....\n");
		do
		{
			printf(" Anymore Appointment to modify(Y=Yes,N=No): ");
			rewind(stdin);
			scanf("%c", &choose);
		} while (toupper(choose) != 'Y' && toupper(choose) != 'N');
	}

	*appmtMod = totalModify;
	fwrite(&appmt, sizeof(appmt), 1, ModifyBin);
	printf(" Total %d appointment records have been successfully modify\n\n", totalModify);

	fclose(ModifyBin);
}
void deleteAppointment(int*appmtDel)
{
	FILE *dReadBin;
	dReadBin = fopen("appointmentRecord.bin", "rb");

	int i = 0, count = 0;

	while (fread(&appointment, sizeof(appointment), 1, dReadBin) != 0)
	{
		if (appointment.gender != '\0')
		{
			appmt[i] = appointment;
			count++;
			i++;
		}
	}
	fclose(dReadBin);

	FILE *DeleteBin;
	DeleteBin = fopen("appointmentRecord.bin", "wb");

	int totalDelete = 0, get;
	char choose, sure;

	do
	{
		printf("\n Delete Appointment?(Y=Yes,N=No): ");
		rewind(stdin);
		scanf("%c", &choose);
	} while (toupper(choose) != 'Y' && toupper(choose) != 'N');

	while (toupper(choose) == 'Y')
	{
		get = 0;
		printf("\n Search >>\n");
		printf(" Patient ID                        : ");
		rewind(stdin);
		scanf("%[^\n]", &appointment.ptID);
		printf(" Appointment Date (day-month-year) : ");
		rewind(stdin);
		scanf("%d-%d-%d", &appointment.appmtDate.day, &appointment.appmtDate.month, &appointment.appmtDate.year);
		printf(" Appointment Time (hrs:time)       : ");
		rewind(stdin);
		scanf("%d:%d", &appointment.fromTime.hrs, &appointment.fromTime.min);

		for (i = 0; i < count; i++)
		{
			if (strcmp(appmt[i].ptID, appointment.ptID) == 0 && appmt[i].appmtDate.day == appointment.appmtDate.day && appmt[i].appmtDate.month == appointment.appmtDate.month
				&& appmt[i].appmtDate.year == appointment.appmtDate.year && appmt[i].fromTime.hrs == appointment.fromTime.hrs && appmt[i].fromTime.min == appointment.fromTime.min)
			{
				printf(" %2d-%2d-%2d    %-6s   %-10s   %-6c   %-13s   %-16s   %02d:%02d    %02d:%02d    %-10s   %2d-%2d-%2d   %-20s\n", appmt[i].todayDate, appmt[i].ptID, appmt[i].ptName,
					appmt[i].gender, appmt[i].nrsName, appmt[i].drName, appmt[i].fromTime, appmt[i].toTime, appmt[i].week, appmt[i].appmtDate, appmt[i].remark);

				printf(" Sure to remove?(Y=Yes,N=No): ");
				rewind(stdin);
				scanf("%c", &sure);
				if (toupper(sure) == 'Y')
				{
					delTrack[totalDelete] = appmt[i];
					do
					{
						appmt[i] = appmt[i + 1];
						i++;
					} while (i < count);
					count--;
					totalDelete++;
					printf(" Data has been succesfully Delete....\n\n");
				}
				else
					printf(" Appointment delete fail to proceed\n\n");
				get = 1;
			}
		}
		if (get == 0)
			printf("\n Undefined appointment record....\n");

		do
		{
			printf(" Any Appointment to delete?(Y=Yes,N=No): ");
			rewind(stdin);
			scanf("%c", &choose);
		} while (toupper(choose) != 'Y' && toupper(choose) != 'N');
	}
	*appmtDel = totalDelete;
	fwrite(&appmt, sizeof(appmt), 1, DeleteBin);
	printf(" Total %d appointment records have been successfully deleted\n\n", totalDelete);
	fclose(DeleteBin);
}
void trackReport(int appmtMod, int appmtDel, int appmtAdd, int appmtFd)
{
	FILE *TRBin;
	TRBin = fopen("appointmentTrack.bin", "wb");

	int i;

	printf("\n Appointment System Tracking Report \t\t\n");
	printf(" ------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
	printf(" Total appointment successfully found    : \t%0d\n", appmtFd);
	printf(" Total appointment successfully modified : \t%0d\n", appmtMod);
	for (i = 0; i < appmtMod; i++)
	{
		printf(" %2d-%2d-%2d    %-6s   %-10s   %-6c   %-13s   %-16s   %02d:%02d    %02d:%02d    %-10s   %2d-%2d-%2d   %-20s\n", modTrack[i].todayDate, modTrack[i].ptID, modTrack[i].ptName,
			modTrack[i].gender, modTrack[i].nrsName, modTrack[i].drName, modTrack[i].fromTime, modTrack[i].toTime, modTrack[i].week, modTrack[i].appmtDate, modTrack[i].remark);
	}
	printf("\n");

	printf(" Total appointment successfully deleted  : \t%0d\n", appmtDel);
	for (i = 0; i < appmtDel; i++)
	{
		printf(" %2d-%2d-%2d    %-6s   %-10s   %-6c   %-13s   %-16s   %02d:%02d    %02d:%02d    %-10s   %2d-%2d-%2d   %-20s\n", delTrack[i].todayDate, delTrack[i].ptID, delTrack[i].ptName,
			delTrack[i].gender, delTrack[i].nrsName, delTrack[i].drName, delTrack[i].fromTime, delTrack[i].toTime, delTrack[i].week, delTrack[i].appmtDate, delTrack[i].remark);
	}
	printf("\n");

	printf(" Total appointment successfully added    : \t%0d\n", appmtAdd);
	for (i = 0; i < appmtAdd; i++)
	{
		printf(" %2d-%2d-%2d    %-6s   %-10s   %-6c   %-13s   %-16s   %02d:%02d    %02d:%02d    %-10s   %2d-%2d-%2d   %-20s\n", addTrack[i].todayDate, addTrack[i].ptID, addTrack[i].ptName,
			addTrack[i].gender, addTrack[i].nrsName, addTrack[i].drName, addTrack[i].fromTime, addTrack[i].toTime, addTrack[i].week, addTrack[i].appmtDate, addTrack[i].remark);
	}
	printf("\n");

	printf(" ------------------------------------------------------------------------------------------------------------------------------------------------\n");

	fwrite(&appmtFd, sizeof(int), 1, TRBin);
	fwrite(&appmtMod, sizeof(int), 1, TRBin);
	fwrite(&appmtDel, sizeof(int), 1, TRBin);
	fwrite(&appmtAdd, sizeof(int), 1, TRBin);

	fclose(TRBin);
}