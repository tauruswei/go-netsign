/*
update 5.5.40.60 for kpl
update 5.5.40.59 for cup multi envelope enc&dec
update 5.5.40.58 for pbccn v1.5
update 5.5.40.56 for pdf sign with hash or pfx
update 5.5.40.55 for chinaport
update 5.5.40.54 for facepay
update 5.5.40.51 for multi pdf verify
update 5.5.40.50 for ccfccb
update 5.5.40.48 for pbccn
update 5.5.40.45 for customs&cpucq
update 5.5.40.43 for face2pay
update 5.5.40.42 for chinaport
update 5.5.40.39 for sge
update 5.5.40.33 for slb
update 5.5.40.30 for xml sign set hash alg
update 5.5.40.27 for std:add set timeout msecond
update 5.5.40.26 for std:add wanglian file enc support
update 5.5.40.25 for bcm:add bcm support
update 5.5.40.25 add 
*/
#ifndef _RH_VERIFY_API_H_
#define _RH_VERIFY_API_H_

typedef struct result_param {
		char issuer[256];					/* �䷢��DN*/
		char serialNumber[40];				/* ֤�����к�*/
		char subject[256];					/* ֤������*/
		char notBefore[20];					/* ֤����Ч�ڵ���ʼʱ��*/
		char notAfter[20];					/* ֤����Ч�ڵ���ֹʱ��*/
		char signresult[1024];				/* ǩ�����*/
		unsigned char cert[2048];			/* ֤��Der����*/
		int  certLen;						/* ֤��Der���볤��*/
} CERTINFO;

typedef struct cert_info_ext{
	char Version[8];
	char SignAlg[16];
	char HashAlg[16];
	char PubKey[1024];
	int PubKeyLen;
} CERTINFOEXT;

typedef struct result_dnparam{
	char issuer[256]; /* �䷢��*/
	char serialNumber[40]; /* ֤�����к�SN*/
	char subject[256]; /* ֤������DN*/
	char cn[256];	/* ֤��CN */
	char notBefore[20]; /* ֤����Ч�ڵ���ʼʱ��*/
	char notAfter[20]; /* ֤����Ч�ڵ���ֹʱ��*/
} DNCERTINFO;
typedef struct pdf_sign_param_s{			/* PDFǩ������ */
	char passwd[50];
	int x1;									/*ǩ�������½����꣬��0��ʼ������*/ 
	int y1;									/*ǩ�������½����꣬��0��ʼ������*/
	int x2;									/*ǩ�������Ͻ����꣬��0��ʼ������*/
	int y2;									/*ǩ�������Ͻ����꣬��0��ʼ������*/
	int page; 								/*ǩ����ҳ�룬��1��ʼ������*/
	char stamp[100]; 						/*ͼ���ļ���,ͼ�±������ϴ���ǩ����������, ��nullʱ, �Զ�ʹ��ǩ�����������õ�Ĭ��ͼ��*/
} PDF_SIGN_PARAM;

typedef struct PDFVerifyRet
{
	int iVerify;/*ǩ������� 1 ��ǩ�ɹ��� ����Ϊ���󣬼��������*/
	char filedName[256];/*ǩ����*/
	CERTINFO        certInfo;/*ǩ��֤����Ϣ */
}PDFVerifyRet;

typedef struct bar_code_param_s{ /* �������  */
	double barHeight; /*������߶�*/
	double pixWidth; /*���ؿ��,��λ����*/
	int displayQuitZone;/*�Ƿ���ʾ�հ���1��0��*/
	double quitZoneWidth; /*�հ�������*/
	int displayHumanReadable; /*�����Ƿ���ʾ�˹��Ķ��ַ�*/
	int imageFormat; /*���ص�����ͼƬ��ʽ0:png,1:jpeg*/
} BAR_CODE_PARAM;

typedef struct bar_code_s{ /* �����������  */
	int errorCorrectLevel;
	float aspectRatio;
	float yHeight;
	int imgFormat;
	int encodeMode;
	int barSize;
} BAR_CODE;

typedef struct ConInfos
{
        int     sSock;
        int sPort;                      /*�˿�Ҳ������HA��LB��gMPInfos����*/
        char sHost[128];
        unsigned char sPswd[32];
        int type;
}TConInfo;

typedef struct MPInfos
{
        TConInfo cinfo;
        int              conCnt;        /*�ò���������LB��ʱ����õ�*/
        int              status;        /*0: no this machine; 1: normal; 2: bad*/
}TMPInfo;

typedef struct XMLVerifyRet
{
	int iVerify;/*ǩ������� 1 ��ǩ�ɹ��� ����Ϊ���󣬼��������*/
	char signID[128];/*ǩ�� ID*/
	char uriList[1024];/*uri�б�*/
	CERTINFO        certInfo;/*ǩ��֤����Ϣ */
}XMLVerifyRet;

/*��λģʽ:*/
/*�޲�λ*/
#define INS_PADDING_NON		0x00
/* ��λ,RSA�㷨�Ĳ�λ���ǶԳƼӽ���ʹ�ã�,�����SM2���ܣ�Ҳʹ�����ֵ*/
#define INS_PADDING_PKCS1	0x01
/* ��λ  n��n*/
#define INS_PADDING_PKCS7	0x02
/* ��λ  0x80, 0x00, ......(n-1�� 0x00), (iso7816-4)*/
#define INS_PADDING_PAD80	0x03

/*����ģʽ*/
#define INS_MODE_ECB		(0x0100)
#define INS_MODE_CBC		(0x0200)

typedef struct SymmEncryptParam
{
	char Alg[64];/*�ԳƼ����㷨��  "3DES|AES|SM4..."�� ����Ǵ���keylable�ӽ��ܣ��㷨��������Ϊ����*/
	int mode; /*��λģʽ ���� ����ģʽ INS_PADDING_XXX|INS_MODE_XXX�� ����ǷǶԳ���Կ�� ����Ϊ INS_PADDING_PKCS1*/
	unsigned char iv[32];/*iv ֵ��mode����ΪECBʱ�򣬸�ֵ������*/
	int ivLen;/*iv ����Ч���ȣ�mode����ΪECBʱ�򣬸�ֵΪ0*/
}SymmEncryptParam;

typedef struct DataLV
{
	int len; /*���ݳ���*/
	unsigned char *data;/*ָ���������ݵ�ָ��*/
}DataLV;
typedef struct DataTLV
{
	int tag; /*��������*/
	DataLV data;
}DataTLV;


/*������������ݸ�ʽ*/
/*������	0x00	*/
/*ʮ�������ַ���	0x01	����д��*/
/*Base64�ַ���	0x02*/
typedef enum
{
	INS_ENCODING_BINARY = 0,/*����������*/
	INS_ENCODING_HEXSTRING,/*ʮ�������ַ�������д��*/
	INS_ENCODING_BASE64,/*base64�ַ���*/
}ins_encode_type;


#ifdef __cplusplus
extern "C" {
#endif

/*
	�Ƽ�ʹ��
	������4+5+3+9+6=27
	������
*/


/*
 *	1.	��ȡ���ӿڰ汾��
 */
char* NS_GetVersion( );

/* 
 2.	Base64����
 unsigned char* btSrc	in		����������ݻ�����
 int iSrcLen			in		����������ݳ���
 unsigned char* btRet	out		��Base64����������
 int* piRetLen			in/out	����������/���������ݳ���

 ����:
	  (1)  �� btSrcΪ NULL ����iSrcLen <= 0����������Err_InvalidParam(8001)
	  (2)  �� btRetΪ NULL ���� piRetLen��Ϊ���ʱ�����ָʾbtRet��������С��ֵ̫С(С��(4 *iSrcLen)/3)���������� Err_BuffSizeNotEnough   
	  (3)  ��������º�������0; btRet��ű���������; piRetLen��ű���������
*/
int EncodeBase64(unsigned char* btSrc, int iSrcLen, unsigned char* btRet, int* piRetLen);


/* 
 3.	Base64���� 
 unsigned char* btSrc	in		����������ݻ�����
 int iSrcLen			in		����������ݳ���
 unsigned char* btRet	out		Base64����������
 int* piRetLen			in/out	����������/���������ݳ���

 ����:
	  (1)  �� btSrcΪ NULL ����iSrcLen <= 0 ���� btSrc �ַ����ĳ��Ȳ�����iSrcLen����������Err_InvalidParam(8001)
		   һ��iSrcLen��strlen(btSrc)��ʽ����
	  (2)  �� btRetΪ NULL ���� piRetLen��Ϊ���ʱ�����ָʾbtRet��������С��ֵ̫С(��С��iSrcLen���㹻��)���������� Err_BuffSizeNotEnough   
	  (3)  �����ڲ��ж�̬�����ڴ�(����Ϊ���������ݵĳ���)�Ĳ���, �������ڴ�ʧ���򷵻�-3
	  (4)  ������Զ�����Base64�Ƿ��ַ�
	  (5)  ��������º�������0; btRet��Ž���������; piRetLen��Ž���������
*/ 
int DecodeBase64(unsigned char* btSrc, int iSrcLen, unsigned char* btRet, int* piRetLen);


/* 
4.	��sha1ժҪ 
sha1ժҪ
unsigned char * pMsg		in		��ժҪԭ��
int pMsgLen					in		��ժҪԭ�ĳ���
unsigned char * pDigest		out		ժҪ����
int* pDigestLen				out		ժҪ����

����: 20 		ժҪ����
			����	ʧ��
*/
int SHA1Digest (unsigned char* pMsg, int pMsgLen, unsigned char* pDigest,int* pDigestLen);


/* 
 *  ������
 *  1.	�趨��ʱ(Ĭ��s)
 *
	���ó�ʱʱ��
	int timeout		in			��ʱʱ�䣬�����ʾ

	˵��
		��ʱʱ������������, С�ڵ���0�������ö�ʧ��
		��ʱʱ���������100 ����Ϊ��λ�Ǻ���(5.5.40.26�汾��ʼ�趨)
		ʹ�� SetTimeOutMsec �ӿ��������ӿڡ�

	����ֵ
		0	�ɹ�
		����	ʧ��
*/
int SetTimeOut(int timeout );

/* 
 *  ������
 *  1.	�趨��ʱ(����)(v5.5.40.26 add)
 *
	���ó�ʱʱ��
	int timeout		in			��ʱʱ�䣬�Ժ����ʾ

	˵��
		��ʱʱ������������, С�ڵ���0�������ö�ʧ��
	����ֵ
		0	�ɹ�
		����	ʧ��
*/

int SetTimeOutMsec(int timeout );

/* 
 *  ������
 *  1.	�趨��ʱ(����)(v5.5.40.35 add)
 *
	���ó�ʱʱ��
	int total_timeout	in			�ܳ�ʱʱ�䣬�Ժ����ʾ
	int timeout			in			��ʱʱ�䣬�Ժ����ʾ

	˵��
		��ʱʱ������������, С�ڵ���0�������ö�ʧ�ܡ�
		��ʱʱ��Ϊ����socketͨѶ��ʱʱ�䣬 
		�ܳ�ʱʱ��Ϊ��γ�ʱʱ����ۼ�ʱ�䡣�����ܳ�ʱʱ����Ϊҵ���������ԣ��ط������ơ�
		�����ձ�����Ϊ��ʱʧ�ܺ󣬻�����������ط��������ۼ�ʱ�䳬���ܳ�ʱʱ���API�Żᱨ��
	����ֵ
		0	�ɹ�
		����	ʧ��
*/
int SetTimeOutMsecEx(int total_timeout, int timeout );
/* 
	2.	�趨����ҵ��ʧ�����³��Դ���(Ĭ��1��) 

	�������ӶϿ��������ӳ��Դ���
	int times		in			���ӶϿ��������ӳ��Դ���

	˵��
		�ӿ�������ʱ, �����ͻ��߽���ʧ��, ���Զ��Ͽ���ǰ�������½���һ�������������ͺͽ��յ�ǰ����
		Ĭ���ǳ���һ�Ρ�
		�ɸ�����Ҫ�趨���ԵĴ���
	����ֵ��
	0		�ɹ�
	����		ʧ��

˵��:
(1)Ӧ��������ʱ, ��API��⵽���ӶϿ�, ���᳢���Զ������������Ĵ���Ĭ��Ϊ1��
*/
int SetReConnTimes(int times );


/* 3.	�趨�Ƿ������������ӹ���(Ĭ��������)

	�����Ƿ������������ӹ���
	int sw 	�򿪻��߹ر������������ӹ��ܣ�1��ʾ�򿪣�0��ʾ�ر�
	����ֵ��
	0		�ɹ�
	����		ʧ��

˵��:
(1)Ĭ��״̬���������ӹ�������
*/
int SetHostNameOff(int sw );

 
/* 4.	��ʼ���������� 

	��ʼ����������
	
	����ִ�иó�ʼ��������ֱ�ӽ��в�������, ����������ܻ����
	����ÿ�� ���������� IP�� �˿ڶ���ͬ�Ļ�, �����������
*/ 
void initConnect();


/*
	5. �趨����ʧ��ʱ��ȴ���ʱ��
	int mseconds		in		����ʧ�ܺ��ӳ��˳���ʱ��
	����ֵ
		0�ɹ�
		����ʧ��
	ֻ�ܴ����ڵ���0 ����

 */
int SetSleepTime( int mseconds );




int SetSize4TimeOutPolicy( long size );

/* 
 * ������
 * 1.	��������
 *
	��������
	char* ip		in	ǩ��������ip��ַ, Ҳ֧�ִ�����������������ʽ
	int port		in	ǩ��������ip�˿�
	char* passwd	in	ǩ����������������
	int* sockFd		out	������TCP/IP���Ӿ��
	˵����
	ip����������������ǰ���������������ӹ��ܡ�Ĭ�������ã���û�����ù�������ֱ�ӿɴ�������
	����ֵ
		0	�ɹ�
		����	ʧ��
*/
int ConnToNetSign( char* ip, int port, char* passwd, int* sockFd );
int Connect      ( char* ip, int port, char* passwd, int* sockFd );

/* 2.	�Ͽ�����
 
	�Ͽ�����
	int sockFd			in		socket�׽���
	����ֵ
		0	�ɹ�
		����	ʧ��
*/
int DiscFromNetSign( int sockFd );
int Disconnect     ( int sockFd );





/*
 * ���ؾ�����صĽӿ�
 */


/*
	1. ���ؾ����趨�����Լ�
	int mode		in		�Լ�ģʽ, 0��ʾ�������Լ�; 1��ʾ�����Լ�
	int interval	in		�Լ�Ƶ��, ��λ��, Ĭ����600�룬��10����

 */
int SetLBCheckMode( int mode, int interval );

/*
	1. ������趨�����Լ������ڲ���
	int mode		in		�Լ�ģʽ, 0��ʾ�������Լ�; 1��ʾ�����Լ�
	int interval	in		�Լ�Ƶ��, ��λ��, 0 ����ʹ�ô˲�����,Ĭ��ֵ(600��)��Ϊ�Լ촥�������� -1����ʹ�ô˲�����Ϊ�Լ�����
	int business_number	in	�Լ�Ƶ��, ��λҵ���ۼ�����, 0 ����ʹ�ô˲���Ĭ��ֵ��10000�ʣ���Ϊ�Լ촥�����������ۼ�10000��ҵ������һ���Լ�, -1����ʹ�ô˲�����Ϊ�Լ����� 
	����2�� 3 ����ͬʱΪ0

 */
int SetLBCheckModeEx( int enable, int interval, int numOfMessage);

/* 2.	���ö��������(����HA��LB���ؾ���)

  	����HA���߸��ؾ���
	����˵��
		int type				in		��������, 1��ʾHA, 2��ʾ���ؾ���
		char list[100][80]		in		���õ�HA������Ϣ�б�/���õĸ��ؾ���������Ϣ�б�
		int len					in		���õ������������
		int status[100]			out		���������
	
	˵��:
		(1) ÿ��������Ϣ�ĸ�ʽ��IP�����������˿ڡ�������ð�Ÿ���, ����
			list[0] = "192.168.2.147:40019:mypassword";
		(2) lenΪ���õ�������������, ����HAģʽ���߸��ؾ���ģʽ������������
		(3) ���֧������100������ĸ��ؾ���
		(4) HA ģʽֻ֧������50�Ի���
		(5) ״ֵ̬0��ʾ������������; 8003��ʾ��������ʧ��
	����ֵ
		0�ɹ�		��0ʧ��

 */
#define SLB_TYPE_NORMAL								0	/*normal*/
#define SLB_TYPE_HA									1	/*HA*/
#define SLB_TYPE_LB									2	/*LB*/
#define SLB_TYPE_LBEX								3	/*LBEX*/

int InitServerList( int type, char list[][100], int len, int status[] );

/*���������ļ������������ļ���ȫ·�������ļ�����*/
/*���ini_path Ϊnull�򳤶�Ϊ 0�� ʹ��Ĭ��·����Ĭ�������ļ�[ns_lbsvrlist.conf]*/
int InitServerListByProfile( int type, char *file_path, int *status, int *len );


typedef struct server_state{
	char svr_addr[256];/*server ip*/
	int svr_port;/*server port*/
	char svr_pwd[32];/*api password*/
	int cur_cnt;/*connected count*/
	int avg_used_time_ms;/*avg used time*/
	int svr_state;/*server state:0 normal, 8 delay , 9 disconnect*/
} SERVER_STATE;

int NS_LBGetServersState(SERVER_STATE svr_states[], int *svr_num);

/* 3.	��ȡHA���߸��ؾ��ⷽʽ������
 
	��ȡHA���߸��ؾ��ⷽʽ������
	int* indx			in/out	����HA��ʽ, �������˶��HA����, indx��ʾ����ָ���ĵ�indx������,ע�ⲻ�ǵڼ�̨, ��1��ʼ��
	int* sockFd			out		���Ӿ��
	˵��:
		(1) indx ֻ����ʹ��HA��ʽ���ӵ�ʱ��Ż��õ�
		(2) indx ��1��ʼ��ʼ, ������������2������(��4̨����), �� indx ��ȡֵ��Χ�� 1,2
		(3) indx ��Ϊ���ε�ʱ���ʾHAʵ�����ӵ�������
		(4) indx����ֵΪ1 ��ʾ�����ϵ�indx�������ĵ�1̨; Ϊ 2 ��ʾ�����ϵ�indx�������ĵ�2̨

	����0�ɹ�; ����ʧ��
 */
int GetConncetion( int* indx, int* sockFd );


/*
 *	4. HA �� ���ؾ��ⷽʽ �ϴ�֤��
	int  indx				in	����HA��ʽ, �������˶��HA����, indx��ʾ����ָ���ĵ�indx������,ע�ⲻ�ǵڼ�̨, ���ǵڼ��ԡ���1��ʼ��
	unsigned char* cert		in	��Կ֤������(der���롢Base64����?)
	int iCertLen			in	��Կ֤�����ݳ���
	int* status[]			out	�ϴ����, �����õ�����˳��һһ��Ӧ
	˵����
		status�е�ֵ 0��ʾ�ɹ��ϴ�; ������ʾʧ��
		status�е�״ֵ̬���������õ���������һ��
		indx ����ȡ���Ӵ���ֵһ��, ��������HA��ʽ����
	����
		0	�ɹ�		
		����	ʧ��
 */
int GroupUploadCert(int indx, unsigned char* cert, int iCertLen, int status[] );


/*
 *	5. HA �� ���ؾ��ⷽʽ ɾ��֤��
  
	ɾ��֤��
	int  indx			in	����HA��ʽ, �������˶��HA����, indx��ʾ����ָ���ĵ�indx������,ע�ⲻ�ǵڼ�̨, ���ǵڼ��ԡ���1��ʼ��
	char* signCertDN	in	��Կ֤��DN
	int* status[]		out	�ϴ����, �����õ�����˳��һһ��Ӧ
	˵����
		status�е�ֵ 0��ʾ�ɹ�ɾ��; ������ʾʧ��
		status�е�״ֵ̬���������õ���������һ��
	˵��
		���ⲻ�ܹ�Ϊ��
	����ֵ��
	0		�ɹ�
	����		ʧ��
 */
int GroupDeleteCert( int indx, char* signCertDN, int status[] );

/*
 *	6. ����������ӿڣ������ýӿڣ�
  
	int sockFd				in	ǩ�����������Ӿ��
	int *used_time_ms		out	�����ʱ(��λ���룬 ��������Ϊnull�������غ�ʱ)
	˵��
		�˽ӿ��ǵ����ýӿڣ�����������ڲ��Դ��빤����
	����ֵ��
	0		�ɹ�
	����		ʧ��
 */
int INS_ServerHeartBeat(int sockFd, int * used_time_ms);


/* 
 * ֤����ز���
 * 1.	�ϴ�֤��
 *
	�ϴ�֤��
	int sockFd				in	ǩ�����������Ӿ��
	unsigned char* cert		in	��Կ֤������(der���롢Base64����?)
	int iCertLen			in	��Կ֤�����ݳ���
	����ֵ
		0	�ɹ�
		����	ʧ��
*/				  
int UploadCert(int sockFd, unsigned char* cert, int iCertLen);


/* 2.	ɾ��֤��
 
	ɾ��֤��
	int sockFd			in	ǩ�����������Ӿ��
	char* signCertDN	in	��Կ֤��DN
	˵��
		���ⲻ�ܹ�Ϊ��
	����ֵ��
	0		�ɹ�
	����		ʧ��
*/
int DeleteCert(int sockFd, char* signCertDN);


/* 3.	����֤�������б�
 
	��ȡ֤���б�
	int   sockFd				in	ǩ�����������Ӿ��
	char* pCertDN[][128]		out	��Կ֤��DN�嵥�洢��ַ
	int	  maxCnt				in	���ع�Կ֤��DN�������Ŀ
	int*  retCnt				out	ʵ�ʷ��ص�DN����
����ֵ��
0		�ɹ�
����		ʧ��

˵��:
(1) pCertDN���ⲿӦ�÷�����ͷŴ洢�ռ䣻
(2) ��ǩ���������洢�Ĺ�Կ֤������С��nMaxCnt, �򷵻�ǩ����������ʵ�ʴ��ڵ�֤�������б�
(3) ��ǩ���������洢�Ĺ�Կ֤����������nMaxCnt, �򷵻�nMaxCnt��֤�������б�
(4) pRetCnt���ǵ���ʵ�ʷ��ص�֤���������
(5) maxCnt�������0���ӿڻ����maxCnt��С������ʱ�ڴ����ڴ�������(maxCnt*256), ��maxCnt�����ڴ�����, ���ܻ�����ڴ����ʧ�ܵ��²���ʧ�ܡ�
*/
int GetCertList(int sockFd, char pCertDN[][128], int maxCnt, int* retCnt);


/* 4.	��ȡ֤��ʵ��
 
	����֤��
	int sockFd					in	ǩ�����������Ӿ��
	char* signCertDN			in	��Կ֤��DN
	unsigned char* cert			out	��Կ֤������
	int* iCertLen				out	��Կ֤�����ݳ���
	����ֵ��
	0		�ɹ�
	����		ʧ��
˵��:
(1)��Կ֤������ӦΪDER��ʽ��
(2)certʹ�õ��ڴ����ⲿӦ�÷�����ͷš�
*/
int DownloadCert(int sockFd, char* signCertDN, unsigned char* cert, int* iCertLen);


/* 5.	��ȡ֤����Ϣ

�����кŻ�ȡ��Կ֤����Ϣ
int sockFd				in	ǩ�����������Ӿ��
char* bankID			in	��Ա�к�/��������
CERTINFO* certInfo		out	��Կ֤������

����ֵ��
0		�ɹ�
����		ʧ��

˵��:���մ�����кţ���ȡǩ���������ϱ���ĸ��кŵ�����֤����Ϣ(������der֤��ʵ��)
*/
int GetCert(int sockFd, char* bankID, CERTINFO* certInfo);


/* 6.	���֤���Ƿ񱻵���

	���֤���Ƿ����,֤����ڻ�ȡ֤�飻����CRL
	sockFd,		in		socket���
	signCertDN,	in	֤������

	����ֵ��
	0   �Ϸ�
	��0 ֤��Ƿ�
*/
int CheckCertCRL( int sockFd, char* signCertDN	);


/* 7.	���֤����֤֤����

	���ָ��DN��֤���Ƿ���ǩ���������д��ڣ�֤����ڻ�ȡ֤�飻����֤���֤������֤���Ƿ�ΪCFCAǩ����
	sockFd,		in		socket���
	signCertDN,	in		֤������

	˵��
		���봫����
	����ֵ��
	0   �Ϸ�
	��0 ֤��Ƿ�
*/
int CheckCertChain( int sockFd, char* signCertDN );


/* 8.	���֤���Ƿ����

	���֤���Ƿ����
	sockFd,		in		socket���
	signCertDN,	in	֤������

	˵��
		���봫����

	����ֵ��
	1		����֤��
	0		������
	����		ʧ��
*/
int IsCertExist( int sockFd, char* signCertDN );


/* 9.	���֤����Ч��

	��֤֤����Ч��
	sockFd,			in	socket���
	char* sCertDN	in	��Կ֤��DN

	˵��
		���봫����

	����ֵ��
	0		֤������
	����:		1֤����ڣ�2֤�����쳣��3֤�鴦��֤������б��� 4��֤�鲻����

	˵��:����֤��DN��������֤֤�����Ч��
*/
int verifyCert( int sockFd,char* signCertDN );


/* 9 ext.	���֤����Ч��

	��֤֤����Ч��
	sockFd,			in	socket���
	char* sCertDN	in	��Կ֤��DN

	unsigned char *x509Cert in  ֤������
	int CertLen		in			֤�鳤��

	int *pCertState	out ֤��״̬�� 0 ������ 1֤����ڣ�2֤�����쳣��3֤�鴦��֤������б��� 4��֤�鲻����
	˵��
		����֤�����⣨DN������֤�����ݣ� ����������ѡһ

	����ֵ��
		0		�ɹ�
		����		ʧ��
	0		֤������
	����:		

	˵��:����֤��DN��֤�飬������֤֤�����Ч��
*/
int INS_VerifyCert(int sockFd,char* CertDN , unsigned char *x509Cert, int CertLen, int *pCertStatus);

/* 10.	�ж�֤������
*
* �ж�֤����Rsa֤�黹�ǹ���֤��
* cert				in	֤��Der����
* iCertLen			in	Der֤�鳤��
* 
* ˵��
*	����ΪDer֤��
* ����ֵ��
* 0			Rsa֤��
* 1			����֤��
* ������	֤�����
*/
int	IsRsaCert(unsigned char* cert, int iCertLen);

/* 11.	����֤������
*
* ����֤���а汾�š�ǩ���㷨����ϣ�㷨��֤�鹫Կ
* cert				in	֤��Der����
* iCertLen			in	Der֤�鳤��
* pCertInfoExt		in	֤�������Ϣ�洢��ַ
* ˵��
*	����ΪDer֤��
* ����ֵ��
* 0			�ɹ�
* ������	ʧ��
*/
int ParseCert(unsigned char* pucCert, int iCertLen, CERTINFOEXT* pCertInfoExt);

/* 11.	����֤�����֤������
*
* ����֤�������Ϣ ����չ��Ϣ (�汾�š�ǩ���㷨����ϣ�㷨��֤�鹫Կ)
* cert				in	֤��Der����
* iCertLen			in	Der֤�鳤��
* CERTINFO* certInfo out	��Կ֤������
* pCertInfoExt		out	֤�������Ϣ�洢��ַ
* ˵��
*	����ΪDer֤��
* ����ֵ��
* 0			�ɹ�
* ������	ʧ��
*/
int GetCertInfo(unsigned char* Cert, int nCertLen , CERTINFO* certInfo,CERTINFOEXT* pCertInfoExt);

/*12.	����OID��ȡ֤������չ���ֵ*/
/*
* ����OID��ȡ֤������չ���ֵ
* cert				in		֤��Der����
* iCertLen			in		Der֤�鳤��
* pExtOid			in		����ȡ��Ϣ��OID�ַ���
* char *pValue		in		OID��Ӧֵ(OCTET STRING)��ֵ����������һ������
* int *piValueLen	in/out	OID��Ӧֵ����
* ˵��
*	����ΪDer֤��
* ����ֵ��
* 0			�ɹ�
* ������	ʧ��
*/
int GetExtensionValue(unsigned char* pucCert, int iCertLen, char *pExtOid, int *piCritical, char *pValue, int *piValueLen);

/* 
 * 13 ��ȷɾ��֤��
 *
int sockFd						in	ǩ�����������Ӿ��
char* szCertDN					in	֤��DN(����)
unsigned char* cert				in	ָ��DER�����֤���ַ��ָ�룩
int iCertLen					in  ֤�����ĳ���
����ֵ��
�ɹ�,����0
����	ʧ��,���ش�����

˵��:
(1) signCertDN �� cert+iCertLen ��Ϊ�����ѯ��������ѡһ���룬��ֻ��Ҫ��������һ���������һ���������ΪNULL��0����

*/

int ExactDeleteCert(int sockFd, char* signCertDN, unsigned char* cert, int iCertLen);

/* 
 * 14 ��ȡkeystore������Ϣ
 *
int sockFd						in	ǩ�����������Ӿ��
char* keyID						in	֤��DN(����)����ԿID
KEYSTORE_DATA *data				in	���ص�֤���Կ
����ֵ��
�ɹ�,����0
����	ʧ��,���ش�����

˵��:
(1) ����֤���Կ�������ⲿ����KEYSTORE_DATA::retType=1, ����֤�顣 2 ���ع�Կ, Ҳ�����ⲿ�����ã�Ĭ��0��
(2) ��keystore��ֻ�й�Կ����ʱ��,,��ʹ�ⲿ����Ϊ����֤�飬Ҳ��ֱ�ӷ��ع�Կ
(3) �ⲿ����Ϊ0�� ���ȷ���֤�飬֤�鲻���ڣ�����Կ���ڣ��Ż᷵�ع�Կ��

*/

typedef struct keystore_data {
	unsigned int retType;/*1 ����֤�飬 2 ���ع�Կ*/
	unsigned char signCert[4096];/*����ǩ��֤��*/
	unsigned int signLen;
	unsigned char exchCert[4096];/*���ؼ���֤��*/
	unsigned int exchLen;
} KEYSTORE_DATA;

int INS_GetKeyStoreInfo(int sockFd, char* keyID, KEYSTORE_DATA *data);



/* 
 * ǩ����ǩ
 * 1.	��ǩ��
 *
��ǩ��
int sockFd				in	ǩ�����������Ӿ��
unsigned char* plain	in	ԭʼ���ݵ�ַ
int iPlainLen			in	ԭʼ���ݳ���
char* signCertDN		in	ǩ����֤��DN
unsigned char* crypto	out	ǩ�����ݴ洢��ַ
int* iCryptoLen			out	ǩ������ʵ�ʳ���

����ֵ��
0		�ɹ�
����	ʧ��

˵��:
(1) cryptoʹ�õ��ڴ�ռ��ɵ��ýӿڵ�Ӧ�ó�����������ͷ�;
(2) ǩ�����û�����κ�ת��, ��Ҫת����Base64����������е��ñ��ӿ����ṩ��EncodeBase64�����б���;
(3) ��ǩʱ���͵�ǩ��ֵ�������ʹ�ô˽ӿڷ��صĳ���, ǧ��Ҫ��strlen(crypto)�����ǩ��ֵ���ȣ�

*/

int RawSign(
					 int sockFd, 
					 unsigned char* plain, 
					 int iPlainLen, 
					 char* signCertDN, 
					 unsigned char* crypto, 
					 int* iCryptoLen);


/* 2.	����ǩ
 
	��֤��ǩ
	int sockFd				in	ǩ�����������Ӿ��
	unsigned char* plain	in	ԭʼ���ݵ�ַ
	int iPlainLen			in	ԭʼ���ݳ���
	char* signCertDN		in	ǩ����֤��DN
	unsigned char* crypto	in	ǩ�����ݵ�ַ
	int iCryptoLen			in	ǩ�����ݳ���
	int iReturnCert			in	�Ƿ񷵻�֤����Ϣ 0 false 1 true
	CERTINFO* result		out	֤����Ϣ�洢��ַ
	����ֵ
	0		�ɹ�
	����	ʧ��
˵��:
(1) resultʹ�õ��ڴ�ռ��ɵ��ýӿڵ�Ӧ�ó�����������ͷ�;
(2) ǩ��ֵ���յĸ�ʽ�Ƕ�����
(3) ����ǩ����ΪBase64�ģ������е��ñ��ӿ����ṩ��DecodeBase64�����н����ٽ�����ǩ;
(4) ��ǩʱ���͵�ǩ��ֵ�������ʹ��ǩ��ֵʵ�ʵĳ���, ǧ��Ҫ��strlen(crypto)������ǩ��ֵ���ȣ�

*/
int RawVerify(
					   int sockFd, 
					   unsigned char* plain, 
					   int iPlainLen, 
					   char* signCertDN, 
					   unsigned char* crypto, 
					   int iCryptoLen, 
					   int iReturnCert, 
					   CERTINFO* result);
					   
					   
/* 3.	Simple����ǩ(ֻ��ǩ����Ч�Բ���֤����Ч��{���ڡ���������֤�����쳣})
 
	ֻ��ǩ����Ч�Բ���֤����Ч��{���ڡ���������֤�����쳣}
	int sockFd				in	ǩ�����������Ӿ��
	unsigned char* plain	in	ԭʼ���ݵ�ַ
	int iPlainLen			in	ԭʼ���ݳ���
	char* signCertDN		in	ǩ����֤��DN
	unsigned char* crypto	in	ǩ�����ݵ�ַ
	int iCryptoLen			in	ǩ�����ݳ���
	int iReturnCert			in	�Ƿ񷵻�֤����Ϣ 0 false 1 true
	CERTINFO* result		out	֤����Ϣ�洢��ַ
	����ֵ
		0	�ɹ�
		����	ʧ��
˵��:
(1) resultʹ�õ��ڴ�ռ��ɵ��ýӿڵ�Ӧ�ó�����������ͷ�;
(2) ǩ��ֵ���յĸ�ʽ�Ƕ�����
(3) ����ǩ����ΪBase64�ģ������е��ñ��ӿ����ṩ��DecodeBase64�����н����ٽ�����ǩ;
(4) ��ǩʱ���͵�ǩ��ֵ�������ʹ��ǩ��ֵʵ�ʵĳ���, ǧ��Ҫ��strlen(crypto)������ǩ��ֵ���ȣ�
(5)������CRL������������������֤��ǩ����ΪCFCA��������֤���Ƿ����
*/
int RawVerifySimple(
							 int sockFd, 
							 unsigned char* plain, 
							 int iPlainLen, 
							 char* signCertDN, 
							 unsigned char* crypto, 
							 int iCryptoLen, 
							 int iReturnCert, 
							 CERTINFO* result);
							 
							 
/* 4.	Detachedǩ��
 
	Dettachǩ��
	int sockFd				in	ǩ�����������Ӿ��
	unsigned char* plain	in	ԭʼ���ݵ�ַ
	int iPlainLen			in	ԭʼ���ݳ���
	char* signCertDN		in	ǩ����֤��DN
	unsigned char* crypto	out	ǩ�����ݵ�ַ
	int* iCryptoLen			out	ǩ�����ݳ���
	����ֵ
		0	�ɹ�
		����	ʧ��
˵��:
(1) cryptoʹ�õ��ڴ�ռ��ɵ��ýӿڵ�Ӧ�ó�����������ͷ�;
(2) ǩ�����û�����κ�ת��, ��Ҫת����Base64����������е��ñ��ӿ����ṩ��EncodeBase64�����б���;
(3) ��ǩʱ���͵�ǩ��ֵ�������ʹ�ô˽ӿڷ��صĳ���, ǧ��Ҫ��strlen(crypto)�����ǩ��ֵ���ȣ�

*/
int DetachedSign(
						  int sockFd, 
						  unsigned char* plain, 
						  int iPlainLen, 
						  char* signCertDN, 
						  unsigned char* crypto, 
						  int* iCryptoLen);
						  
						  
/* 5.	Detached��ǩ��
 
	Dettached��ǩ
	int sockFd				in	ǩ�����������Ӿ��
	unsigned char* plain	in	ԭʼ���ݵ�ַ
	int iPlainLen			in	ԭʼ���ݳ���
	unsigned char* crypto	in	ǩ�����ݵ�ַ
	int iCryptoLen			in	ǩ�����ݳ���
	int iReturnCert			in	֤��ѡ�� 0:������֤��ʵ��; 1: ����֤�鼰֤��ʵ��; 2: ɾ��֤��; 3: �ϴ�֤�� 
	CERTINFO* result		out	֤����Ϣ�洢��ַ
	����ֵ
		0	�ɹ�
		����	ʧ��
˵��:
(1) resultʹ�õ��ڴ�ռ��ɵ��ýӿڵ�Ӧ�ó�����������ͷ�;
(2) ǩ��ֵ���յĸ�ʽ�Ƕ�����
(3) ����ǩ����ΪBase64�ģ������е��ñ��ӿ����ṩ��DecodeBase64�����н����ٽ�����ǩ;
(4) ��ǩʱ���͵�ǩ��ֵ�������ʹ��ǩ��ֵʵ�ʵĳ���, ǧ��Ҫ��strlen(crypto)������ǩ��ֵ���ȣ�

*/
int DetachedVerify(
							int sockFd, 
							unsigned char* plain, 
							int iPlainLen, 
							unsigned char* crypto, 
							int iCryptoLen, 
							int iReturnCert, 
							CERTINFO* result);

							
							
/* 6.	Simple Detached��ǩ(ֻ��ǩ����Ч�Բ���֤����Ч��{���ڡ���������֤�����쳣})
 
	����֤���Dettached��ǩ
	int sockFd				in	ǩ�����������Ӿ��
	unsigned char* plain	in	ԭʼ���ݵ�ַ
	int iPlainLen			in	ԭʼ���ݳ���
	unsigned char* crypto	in	ǩ�����ݵ�ַ
	int iCryptoLen			in	ǩ�����ݳ���
	int iReturnCert			in	�Ƿ񷵻�֤����Ϣ 0 false 1 true
	CERTINFO* result		out	֤����Ϣ�洢��ַ
	����ֵ
		0	�ɹ�
		����	ʧ��
˵��:
(1) resultʹ�õ��ڴ�ռ��ɵ��ýӿڵ�Ӧ�ó�����������ͷ�;
(2) ǩ��ֵ���յĸ�ʽ�Ƕ�����
(3) ����ǩ����ΪBase64�ģ������е��ñ��ӿ����ṩ��DecodeBase64�����н����ٽ�����ǩ;
(4) ��ǩʱ���͵�ǩ��ֵ�������ʹ��ǩ��ֵʵ�ʵĳ���, ǧ��Ҫ��strlen(crypto)������ǩ��ֵ���ȣ�
(5) ������CRL������������������֤��ǩ����ΪCFCA��������֤���Ƿ���ڣ�
*/
int DetachedVerifySimple(
								  int sockFd, 
								  unsigned char* plain, 
								  int iPlainLen, 
								  unsigned char* crypto, 
								  int iCryptoLen, 
								  int iReturnCert, 
								  CERTINFO* result);


/*	7.	EncryptEnvelope���������ŷ�
		int sockFd				in	ǩ�����������Ӿ��
		unsigned char* plain	in	ԭʼ���ݵ�ַ
		int iPlainLen			in	ԭʼ���ݳ���	
		char* enCertDN			in	����֤��DN
		unsigned char* crypto	out �����ŷ�����
		int* iCryptoLen			out �����ŷⳤ��

		����ֵ
		0	�ɹ�
		����	ʧ��

*/
int EncryptEnvelope(int sockFd, unsigned char* plain, int iPlainLen, char* enCertDN,
	unsigned char* crypto, int* iCryptoLen);




/*	8.	DecryptEnvelop���������ŷ�
		int sockFd				in	ǩ�����������Ӿ��
		unsigned char* crypto	in  �����ŷ�����
		int iCryptoLen			in  �����ŷⳤ��
		char* enCertDN			in	����˽ԿDN
		unsigned char* plain	out	ԭʼ����
		int *iPlainLen			out	ԭʼ���ݳ���
		CERTINFO *cinfo			out ԭ����֤����Ϣ
*/
int DecryptEnvelop(int sockFd, unsigned char* crypto, int iCryptoLen, char* enCertDN,
	unsigned char* plain, int* iPlainLen);
				



/* 
 * ���Ƽ�ʹ��
 * ������+4+3+18=28
 * ������
 * 1.	�Ƚ�SHA1ժҪ
 */

/*
sha1ժҪ�Ƚ�, �жϴ�ԭ�ĵ�ժҪ�Ƿ��Ǵ�ժҪ
msg			in ��ժҪԭ��
msgLen		in ��ժҪԭ�ĳ���
dig			in ժҪ����
digLen		in ժҪ����

˵����
	1. ��ժҪԭ�����ݲ����κ�ת�붯��
	2. ժҪ�����Ƕ���������

����:		0 		��ͬ
		����		��ͬ
*/
int SHA1DigestCMP( unsigned char* msg, int msgLen, unsigned char* dig,int digLen );


/*
 * 2.	��Base64��ʽ��SHA1ժҪ
 */
/*
sha1ժҪ
unsigned char* msg			in ��ժҪԭ��
int msgLen					in ��ժҪԭ�ĳ���
unsigned char* digBase64	out ժҪ����,base64����
int* digBase64Len			out base64��ժҪ����

����: 28 		ժҪ����
			����	ʧ��
*/
int SHA1Digest_Base64(unsigned char* msg, int msgLen, unsigned char* digBase64, int* digBase64Len );



/*
 * 3.	�Ƚ�Base64��ʽ��SHA1ժҪ
 */
/*
sha1ժҪ�Ƚ�
unsigned char*	msg			in ��ժҪԭ��
int				msgLen		in ��ժҪԭ�ĳ���
unsigned char*	digB64		in ժҪ����,base64����
int				digB64Len	in ժҪ����

����:		0 		��ͬ
			����	��ͬ
*/
int SHA1DigestCMP_Base64 (unsigned char* msg, int msgLen, unsigned char* digB64,int digB64Len);




/* 
 * ������
 */

/*
 * 1.	ֱ�ӳ�ʼ�������Ӳ���*/
/*
	ֱ�����ó�ʼ������
	char* ip		in	������ip��ַ
	int port		in	���ӵĶ˿ں�
	int timeout		in	��ʱʱ��, ��λ����
	char* passwd	in	���ӷ���������
	˵����
		1. ���������� �ӿ������� "NS_" Ϊ�׵ĺ���
		2. ͬһʱ��ֻ������һ̨��������Ϣ
		3. ����ε��ñ��ӿ�, ��������õ���Ϣ���Ḳ��֮ǰ�����õ���Ϣ
	����ֵ
		0	�ɹ�
		����	ʧ��
*/
int NS_init( char* ip, int port, int msec_timeout, char* passwd );


/*
 * 2.	�����ļ���ʽ��ʼ����������Ϣ*/
/*
	�������ļ����ó�ʼ������
	char* cfgName		in �����ļ�·��
	�����ļ���ʽ���£�
	ip=192.168.0.197
	port=10002
	password=60000
	
	˵����
		1. ����һ����ֱ�ӳ�ʼ������һ��
		2. ���ö�������ֱ�ӳ�ʼ��ʧ��, �����Ӹ������ļ��е�����

	����ֵ
		0	�ɹ�
		����	ʧ��
*/
int NS_SetConfigFile( char* cfgName );



/* 
 * 3.	������־�ļ�*/
/*
	������־�ļ�
	char* logfile	in	��־����ļ���
	����ֵ��
	0		�ɹ�
	����		ʧ��

˵��:
(1)	�˽ӿ��ѱ��ϳ�, û���κ�����
(2)	�Ѿ��õ��Կ����, ����鿴��־, �����Կ��滻���еĿ��ļ�, ����Ļ����ض�����־�ļ�����
(3)	ԭ�ӿ�˵������sFileName��NULL��������־�������ʱAPI���Խ��ڲ�������־��¼��ָ�����ļ��У���sFileNameΪNULL����ر���־������ܣ���ʱAPI��������κ���־��Ϣ����Ļ���ļ���

*/
int SetLogFile(char* logfile);



/*
 * 4.	���õ���ģʽ(Ĭ�Ϸǵ���ģʽ)*/
/*
���õ���ģʽ
int flag  in  1,�������ģʽ,0�˳�����ģʽ
˵��
(1)	�˽ӿ��ѱ��ϳ�, û���κ�����
(2)	�Ѿ��õ��Կ����, ����鿴��־, �����Կ��滻���еĿ��ļ�, ����Ļ����ض�����־�ļ�����

*/
int NS_SetDebugMode( int flag );


/*
 * ֤����ز���
 * 1.	������֮�ϴ�֤��*/
/*
�ϴ�֤��

unsigned char* cert		in	��Կ֤������
int iCertLen			in	��Կ֤�����ݳ���
����ֵ��
0		�ɹ�
����	ʧ��
*/
int NS_UploadCert(unsigned char* cert, int iCertLen);


/*
 * 2.	������֮�ϴ�֤����֤�к�*/
/*
�ϴ�֤��
unsigned char* cert		in	��Կ֤������
int iCertLen			in	��Կ֤�����ݳ���
char* BankID			in  �����к�
˵����
	�ϴ�֤��ͬʱ��֤�к�, ���к���֤���кŲ�ƥ���������ϴ�
����ֵ��
0		�ɹ�
����	ʧ��
*/	  
int NS_UploadCertWithBankID(unsigned char* cert, int iCertLen,char* BankID);


/*
 * 3.	������֮ɾ��֤��
 */
/*
ɾ��֤��
char* signCertDN ��ɾ��֤��DN
����ֵ��
0		�ɹ�
����	ʧ��
*/
int NS_DeleteCert( char* signCertDN );


/* 
 * ǩ����ǩ
 * 1.	������֮����ǩ������Ĭ������˽Կ���������ơ�*/
/*
��ǩ��,ʹ�÷��������õ�ǩ��֤��

unsigned char* plain	in	ԭʼ���ݵ�ַ
int iPlainLen			in	ԭʼ���ݳ���
unsigned char* crypto	out	ǩ�����ݴ洢��ַ,�����Ƹ�ʽ
int* iCryptoLen			out	ǩ������ʵ�ʳ���

����ֵ��
0		�ɹ�
����	ʧ��

˵��:
(1) cryptoʹ�õ��ڴ�ռ����ⲿӦ�ø���������ͷ�;
(2) ǩ��������������κ�ת�붯����
(3) ǩ��ʹ��ϵͳ���õ�ǩ��֤��,api���ṩ֤��DN��Ϣ
*/
int NS_RawSign(
					  unsigned char* plain,
					  int iPlainLen,	
					  unsigned char* crypto,
					  int* iCryptoLen );


/*
 * 2.	������֮����ǩ������Ĭ������˽Կ����Base64��*/
/*
��ǩ��,ʹ�÷��������õ�ǩ��֤��

unsigned char* plain	in	ԭʼ���ݵ�ַ
int iPlainLen			in	ԭʼ���ݳ���
unsigned char* crypto	out	ǩ�����ݴ洢��ַ,base64��ʽ
int* iCryptoLen			out	ǩ������ʵ�ʳ���
����ֵ��
0		�ɹ�
����	ʧ��

˵��:
(1) cryptoʹ�õ��ڴ�ռ����ⲿӦ�ø���������ͷ�;
(2) ǩ��������������κ�ת�붯����
(3) ǩ��ʹ��ϵͳ���õ�ǩ��֤��,api���ṩ֤��DN��Ϣ
(4) ǩ�����ΪBase64����
*/
int NS_RawSign_Base64(
					  unsigned char* plain,
					  int iPlainLen,					  
					  unsigned char* crypto,
					  int* iCryptoLen );


/*
 * 3.	������֮����ǩ������֤�����⡿�������ơ�(�ӿ�����������)*/
/*
��ǩ��
char* signCertDN		in	��ǩ֤������
unsigned char* plain	in	ԭʼ���ݵ�ַ
int iPlainLen			in	ԭʼ���ݳ���
unsigned char* crypto	out	ǩ�����ݴ洢��ַ,������
int* iCryptoLen			out	ǩ������ʵ�ʳ���


����ֵ��
0		�ɹ�
����	ʧ��

˵��:
(1) cryptoʹ�õ��ڴ�ռ����ⲿӦ�ø���������ͷ�;
(2) ǩ��������������κ�ת�붯����
(3) ǩ��ʹ��api�ṩ֤��DN��Ϣ

*/
int NS_RawSignByDN(char* signCertDN , unsigned char* plain, int iPlainLen,  unsigned char* crypto, int* iCryptoLen);



/*
 * 4.	������֮����ǩ������֤�����⡿��Base64��(�ӿ���������)*/
/*
��ǩ��,ʹ�÷��������õ�ǩ��֤��
unsigned char* plain	in	ԭʼ���ݵ�ַ
int iPlainLen			in	ԭʼ���ݳ���
unsigned char* crypto	out	ǩ�����ݴ洢��ַ,base64��ʽ
int* iCryptoLen			out	ǩ������ʵ�ʳ���
����ֵ��
0		�ɹ�
����	ʧ��
˵��:
(1) cryptoʹ�õ��ڴ�ռ����ⲿӦ�ø���������ͷ�;
(2) ǩ�����ݽ��ΪBase64��ʽ�ı��롣
(3) ǩ��ʹ��api�ṩ֤��DN��Ϣ

*/
int NS_RawSignByDN_Base64(unsigned char* plain, int iPlainLen,char* signerDN,  unsigned char* crypto, int* iCryptoLen);

/*
 * 5.	������֮������ǩ����֤�����⡿�������ơ�*/
/*
����֤��DN��֤��ǩ

unsigned char* plain	in	ԭʼ���ݵ�ַ
int iPlainLen			in	ԭʼ���ݳ���
char* signCertDN		in	ǩ����֤��DN�����к�
unsigned char* crypto	in	ǩ�����ݵ�ַ,�����Ƹ�ʽ
int iCryptoLen			in	ǩ�����ݳ���
int iReturnCert			in	�Ƿ񷵻�֤����Ϣ 0 false 1 true
CERTINFO* cinfo			out	֤����Ϣ�洢��ַ

����ֵ��
0		�ɹ�
����	ʧ��

˵��:
(1) cinfo ʹ�õ��ڴ�ռ����ⲿӦ�ø���������ͷ�
(2) ����ǩ���ݸ�ʽ�Ķ����Ƶ�
*/
int NS_RawVerify(
					  unsigned char* plain,
					  int iPlainLen,
					  char* signCertDN,
					  unsigned char* crypto,
					  int iCryptoLen,
					  int iReturnCert, 
					  CERTINFO* cinfo);


/*
 * 6.	������֮������ǩ����֤�����⡿��Base64��*/
/*
����֤��DN��֤��ǩ
unsigned char* plain	in	ԭʼ���ݵ�ַ
int iPlainLen			in	ԭʼ���ݳ���
char* signCertDN		in	ǩ����֤��DN�����к�
unsigned char* crypto	in	ǩ������Buffer,base64��ʽ
int iCryptoLen			in	ǩ�����ݳ���
int iReturnCert			in	�Ƿ񷵻�֤����Ϣ 0 false 1 true
CERTINFO* cinfo		out	֤����Ϣ�洢��ַ
����ֵ��
0		�ɹ�
����	ʧ��

˵��:
(1) cinfoʹ�õ��ڴ�ռ����ⲿӦ�ø���������ͷ�
(2) ����ǩ���ݸ�ʽ��Base64
*/
int NS_RawVerify_Base64( 
								 unsigned char* plain, 
								 int iPlainLen, 
								 char* signCertDN, 
								 unsigned char* crypto, 
								 int iCryptoLen, 
								 int iReturnCert, 
								 CERTINFO* cinfo);


/*
 * 7.	������֮������ǩ����֤�顿�������ơ�*/
/*
����֤����֤��ǩ
unsigned char* plain	in	ԭʼ���ݵ�ַ
int iPlainLen			in	ԭʼ���ݳ���
unsigned char* crypto	in	ǩ�����ݵ�ַ,�����Ƹ�ʽ
int iCryptoLen			in	ǩ�����ݳ���
unsigned char* cert		in	ǩ����֤��,�����Ƹ�ʽ
int iCertLen			in  ǩ����֤�鳤��
int iReturnCert			in	�Ƿ񷵻�֤����Ϣ 0 false 1 true
CERTINFO* cinfo			out	֤����Ϣ�洢��ַ

����ֵ��
0		�ɹ�
����	ʧ��

˵��:
(1)cinfoʹ�õ��ڴ�ռ����ⲿӦ�ø���������ͷ�
*/
int NS_RawVerifyWithCert( unsigned char* plain, 
								  int iPlainLen, 
								  unsigned char* crypto, 
								  int iCryptoLen,
								  unsigned char* cert, 
								  int iCertLen, 
								  int iReturnCert, 
								  CERTINFO* cinfo );


/*
 * 8.	������֮������ǩ����֤�顿��Base64��*/
/*
����֤����֤��ǩ
unsigned char* plain	in	ԭʼ���ݵ�ַ
int iPlainLen		in	ԭʼ���ݳ���
unsigned char* crypto	in	ǩ������Buffer,Base64��ʽ
int iCryptoLen			in	ǩ�����ݳ���
unsigned char* cert		in	ǩ����֤��buffer,�����Ƹ�ʽ
int iCertLen			in  ǩ����֤��buffer����

int iReturnCert			in	�Ƿ񷵻�֤����Ϣ 0 false 1 true
CERTINFO* result		out	֤����Ϣ�洢��ַ
����ֵ��
0		�ɹ�
����	ʧ��

˵��:
(1)resultʹ�õ��ڴ�ռ����ⲿӦ�ø���������ͷ�
*/
int NS_RawVerifyWithCert_Base64( unsigned char* plain, 
										 int iPlainLen, 
										 unsigned char* crypto, 
										 int iCryptoLen,
										 unsigned char* cert, 
										 int iCertLen, 
										 int iReturnCert, 
										 CERTINFO* cinfo );



/*
 * 9.	������֮������ǩ�����кš��������ơ�*/
/*
����֤����֤��ǩ
unsigned char* plain	in	ԭʼ���ݵ�ַ
int iPlainLen			in	ԭʼ���ݳ���
char* BankID			in	�кŻ���֤������
unsigned char* crypto	in	ǩ�����ݵ�ַ,�����Ƹ�ʽ
int iCryptoLen			in	ǩ�����ݳ���
int iReturnCert			in	�Ƿ񷵻�֤����Ϣ 0 false 1 true
CERTINFO* cinfo			out	֤����Ϣ�洢��ַ

����ֵ��
0		�ɹ�
����	ʧ��

˵��:
(1) cinfoʹ�õ��ڴ�ռ����ⲿӦ�ø���������ͷ�
*/
int NS_RawVerifyByBandID(					  
					  unsigned char* plain,
					  int iPlainLen,
					  char* BankID,
					  unsigned char* crypto,
					  int iCryptoLen,
					  int iReturnCert, 
					  CERTINFO* cinfo);





/*
 * 10.	������֮��Detachedǩ������Ĭ������˽Կ���������ơ�(�ӿ�����������)*/
/*
Dettachǩ��,ʹ�÷��������õ�ǩ��֤��
unsigned char* plain	in	ԭʼ���ݵ�ַ
int iPlainLen			in	ԭʼ���ݳ���
unsigned char* crypto	out	ǩ�����ݵ�ַ,�����Ƹ�ʽ
int* iCryptoLen			out	ǩ�����ݳ���
����ֵ��
0		�ɹ�
����	ʧ��
˵��:
(1) cryptoʹ�õ��ڴ�ռ����ⲿӦ�ø���������ͷţ�
(2) ǩ��ʹ��ϵͳ���õ�ǩ��֤��,api���ṩ֤��DN��Ϣ
*/
int NS_DetachedSign( unsigned char* plain, int iPlainLen, unsigned char* crypto, int* iCryptoLen);




/*
 * 11.	������֮��Detachedǩ������Ĭ������˽Կ����Base64��(�ӿ���������)
 */
/*
Dettachǩ��,ʹ�÷��������õ�ǩ��֤��
unsigned char* plain	in	ԭʼ���ݵ�ַ
int iPlainLen			in	ԭʼ���ݳ���
unsigned char* crypto	out	ǩ�����ݵ�ַ,base64��ʽ
int* iCryptoLen			out	ǩ�����ݳ���
����ֵ��
0		�ɹ�
����	ʧ��
˵��:
(1) cryptoʹ�õ��ڴ�ռ����ⲿӦ�ø���������ͷţ�
(2) ǩ��ʹ��ϵͳ���õ�ǩ��֤��,api���ṩ֤��DN��Ϣ
*/
int NS_DetachedSign_Base64( 
	unsigned char* plain, int iPlainLen, 
	unsigned char* crypto, int* iCryptoLen);



/*
 * 12.	������֮��Detachedǩ������֤�����⡿�������ơ�(�ӿ�����������)*/
/*
Dettachǩ��,ʹ�÷��������õ�ǩ��֤��
char* signerDN			in	ǩ��֤������
unsigned char* plain	in	ԭʼ���ݵ�ַ
int iPlainLen			in	ԭʼ���ݳ���
unsigned char* crypto	out	ǩ�����ݵ�ַ,�����Ƹ�ʽ
int* iCryptoLen			out	ǩ�����ݳ���
����ֵ��
0		�ɹ�
����	ʧ��

˵��:
(1) cryptoʹ�õ��ڴ�ռ����ⲿӦ�ø���������ͷţ�
(2) ǩ��ʹ��ϵͳ���õ�ǩ��֤��,api���ṩ֤��DN��Ϣ
*/
int NS_DetachedSignByDN( char* signerDN, unsigned char* plain, int iPlainLen,unsigned char* crypto, int* iCryptoLen);



/*
 * 13.	������֮��Detachedǩ������֤�����⡿��Base64��(�ӿ���������)
 */
/*
Dettachǩ��,ʹ�÷��������õ�ǩ��֤��
unsigned char* plain	in	ԭʼ���ݵ�ַ
int iPlainLen			in	ԭʼ���ݳ���
char* signerDN			in	ǩ��֤������
unsigned char* crypto	out	ǩ�����ݵ�ַ,base64��ʽ
int* iCryptoLen			out	ǩ�����ݳ���
����ֵ��
0		�ɹ�
����	ʧ��

˵��:
(1) cryptoʹ�õ��ڴ�ռ����ⲿӦ�ø���������ͷţ�
(2) ǩ��ʹ��ϵͳ���õ�ǩ��֤��,api���ṩ֤��DN��Ϣ
*/
int NS_DetachedSignByDN_Base64( unsigned char* plain, int iPlainLen, char* signerDN,unsigned char* crypto, int* iCryptoLen);



/*
 * 14.	������֮��Detached��ǩ���������ơ���ɾ���ϴ���*/
/*
Dettached��ǩ
unsigned char* plain	in	ԭʼ���ݵ�ַ
int iPlainLen			in	ԭʼ���ݳ���
unsigned char* crypto	in	ǩ�����ݵ�ַ,�����Ƹ�ʽ
int iCryptoLen			in	ǩ�����ݳ���
int bCertFlag			in	֤�鴦���� 0 �ϴ�֤�� 1 ɾ��֤��
CERTINFO* cinfo			out	֤����Ϣ�洢��ַ
����ֵ��
0		�ɹ�
����	ʧ��
˵��:
(1)resultʹ�õ��ڴ�ռ����ⲿӦ�ø���������ͷ�
*/
int NS_DetachedVerify( unsigned char* plain, int iPlainLen, 
												  unsigned char* crypto, int iCryptoLen, 
												  int bCertFlag, CERTINFO* cinfo);


/*
 * 15.	������֮��Detached��ǩ����Base64����ɾ���ϴ���*/
/*
Dettached��ǩ
unsigned char* plain	in	ԭʼ���ݵ�ַ
int iPlainLen			in	ԭʼ���ݳ���
unsigned char* crypto	in	ǩ�����ݵ�ַ,base64��ʽ
int iCryptoLen			in	ǩ�����ݳ���
int bCertFlag			in	֤�鴦���� 0 �ϴ�֤�� 1 ɾ��֤��
CERTINFO* cinfo			out	֤����Ϣ�洢��ַ
����ֵ��
0		�ɹ�
����	ʧ��
˵��:
(1)cinfoʹ�õ��ڴ�ռ����ⲿӦ�ø���������ͷ�
*/
int NS_DetachedVerify_Base64( 
									  unsigned char* plain, 
									  int iPlainLen, 
									  unsigned char* crypto, 
									  int iCryptoLen, 
									  int bCertFlag, 
									  CERTINFO* cinfo);


/*
 * 16.	������֮��Detached��ǩ���������ơ��������к��ϴ�����ɾ����*/
/*
Dettached��ǩ
unsigned char* plain	in	ԭʼ���ݵ�ַ
int iPlainLen			in	ԭʼ���ݳ���
unsigned char* crypto	in	ǩ�����ݵ�ַ,�����Ƹ�ʽ
int iCryptoLen			in	ǩ�����ݳ���
char* BankID			in  �����к�
int bCertFlag			in	֤�鴦���� 0 �ϴ�֤�� 1 ɾ��֤��
CERTINFO* cinfo			out	֤����Ϣ�洢��ַ
����ֵ��
0		�ɹ�
����	ʧ��
˵��:
(1)cinfoʹ�õ��ڴ�ռ����ⲿӦ�ø���������ͷ�
*/
int NS_DetachedVerifyWithBankID( 
	unsigned char* plain, 
	int iPlainLen, 
	unsigned char* crypto, 
	int iCryptoLen,
	char* BankID,
	int bCertFlag, 
	CERTINFO* cinfo);



/*
 * 17.	������֮��Detached��ǩ����Base64���������к��ϴ�����ɾ����*/
/*
Dettached��ǩ

unsigned char* plain	in	ԭʼ���ݵ�ַ
int iPlainLen			in	ԭʼ���ݳ���
unsigned char* crypto	in	ǩ�����ݵ�ַ,base64��ʽ
int iCryptoLen			in	ǩ�����ݳ���
char* BankID			in  �����к�
int bCertFlag			in	֤�鴦���� 0 �ϴ�֤�� 1 ɾ��֤��
CERTINFO* cinfo		out	֤����Ϣ�洢��ַ
����ֵ��
0		�ɹ�
����	ʧ��
˵��:
(1)cinfoʹ�õ��ڴ�ռ����ⲿӦ�ø���������ͷ�
*/
int NS_DetachedVerifyWithBankID_Base64( 
	unsigned char* plain, 
	int iPlainLen, 
	unsigned char* crypto, 
	int iCryptoLen,
	char* BankID, 
	int bCertFlag, 
	CERTINFO* cinfo);



/*
 * 18.	������֮��Detached��ǩ����Base64����ɾ���ϴ����������������� */
/*
ָ��ip��Dettached��֤����ָ����ǩ������������֤ǩ����ͬʱ�ڸ÷������Ͻ���֤����ϴ���ɾ��

char* ip					in	ǩ��������ip
int port					in	ǩ���������˿�
unsigned char* plain		in	ԭʼ���ݵ�ַ
int iPlainLen				in	ԭʼ���ݳ���
unsigned char* crypto		in	ǩ�����ݵ�ַ,,base64��ʽ
int iCryptoLen				in	ǩ�����ݳ���
int bCertFlag				in	֤�鴦���� 0 �ϴ�֤�� 1 ɾ��֤��
CERTINFO* cinfo				out	֤����Ϣ�洢��ַ
����ֵ��
0		�ɹ�
����	ʧ��
˵��:
(1)cinfo ʹ�õ��ڴ�ռ����ⲿӦ�ø���������ͷ�
*/
int NS_DetachedVerifyWithIP_Base64( 
	char* ip , 
	int port ,
	unsigned char* plain, 
	int iPlainLen, 
	unsigned char* crypto, 
	int iCryptoLen, 
	int bCertFlag, 
	CERTINFO* cinfo);



/* ���ƵĽӿ�
 */
/* 1.	�Ǳ�׼��ʽ��detachedǩ��					  
 
	Dettachǩ��
	int sockFd				in	ǩ�����������Ӿ��
	unsigned char* plain	in	ԭʼ���ݵ�ַ
	int iPlainLen			in	ԭʼ���ݳ���
	char* signCertDN		in	ǩ����֤��DN
	char* format			in	ָ����ʽ�ı�ʶ��
	unsigned char* crypto	out	ǩ�����ݵ�ַ
	int* iCryptoLen			out	ǩ�����ݳ���
	����ֵ
		0	�ɹ�
		����	ʧ��
˵��:
(1) cryptoʹ�õ��ڴ�ռ��ɵ��ýӿڵ�Ӧ�ó�����������ͷ�;
(2) ǩ�����û�����κ�ת��, ��Ҫת����Base64����������е��ñ��ӿ����ṩ��EncodeBase64�����б���;
(3) ��ǩʱ���͵�ǩ��ֵ�������ʹ�ô˽ӿڷ��صĳ���, ǧ��Ҫ��strlen(crypto)�����ǩ��ֵ���ȣ�
(4) ��������֧���Ϻ�ͬ�������formatֵΪ"PBCSHLC"

*/
int CustomDetachedSign(
						  int sockFd, 
						  unsigned char* plain, 
						  int iPlainLen, 
						  char* signCertDN, 
						  char* format,
						  unsigned char* crypto, 
						  int* iCryptoLen);

/* 2.	�Ǳ�׼��ʽ��detached��ǩ
 
	�Ǳ�׼��ʽ��detached��ǩ
	int sockFd				in	ǩ�����������Ӿ��
	unsigned char* plain	in	ԭʼ���ݵ�ַ
	int iPlainLen			in	ԭʼ���ݳ���
	unsigned char* crypto	in	ǩ�����ݵ�ַ
	int iCryptoLen			in	ǩ�����ݳ���
	int iReturnCert			in	�Ƿ񷵻�֤����Ϣ 0 false 1 true
	char* format			in	ָ����ʽ��p7ǩ����ʶ��
	CERTINFO* result		out	֤����Ϣ�洢��ַ
	����ֵ
		0	�ɹ�
		����	ʧ��
˵��:
(1) resultʹ�õ��ڴ�ռ��ɵ��ýӿڵ�Ӧ�ó�����������ͷ�;
(2) ǩ��ֵ���յĸ�ʽ�Ƕ�����
(3) ����ǩ����ΪBase64�ģ������е��ñ��ӿ����ṩ��DecodeBase64�����н����ٽ�����ǩ;
(4) ��ǩʱ���͵�ǩ��ֵ�������ʹ��ǩ��ֵʵ�ʵĳ���, ǧ��Ҫ��strlen(crypto)������ǩ��ֵ���ȣ�
(5) ����format��ʽ��˵��, ��ͬ��Ӧ���̻�����в�ͬ��ֵ
(6) ��������֧���Ϻ�ͬ�������formatֵΪ"PBCSHLC"

*/
int CustomDetachedVerify(
							int sockFd, 
							unsigned char* plain, 
							int iPlainLen, 
							unsigned char* crypto, 
							int iCryptoLen, 
							int iReturnCert,
							char* format,
							CERTINFO* result);



/* 3. �ǳ�����Ľӿ�: Detachedǩ���ɹ�ͬʱ�ϴ�֤��  */
/*
	Dettachǩ�����ϴ�֤��
	int sockFd					in	ǩ�����������Ӿ��
	unsigned char* plain		in	ԭʼ���ݵ�ַ
	int iPlainLen				in	ԭʼ���ݳ���
	char* signCertDN			in	ǩ����֤��DN
	int iUploadCert				in  �Ƿ��ϴ�֤�� 0 false 1 true
	unsigned char* crypto		out	ǩ�����ݵ�ַ
	int* iCryptoLen				out	ǩ�����ݳ���
	����ֵ
		0	�ɹ�
		����	ʧ��
˵��:
(1) cryptoʹ�õ��ڴ�ռ����ⲿӦ�ø���������ͷţ�
*/
int DetachedSignUploadCert(
						  int sockFd, 
						  unsigned char* plain, 
						  int iPlainLen, 
						  char* signCertDN, 
						  int iUploadCert,
						  unsigned char* crypto, 
						  int* iCryptoLen);





/* 
 * ֤����ز���
 * 10.	�ϴ�֤��ָ���к�
 *
	�ϴ�֤��ָ���к�
	int sockFd				in	ǩ�����������Ӿ��
	unsigned char* cert		in	��Կ֤������(der���롢Base64����?)
	int iCertLen			in	��Կ֤�����ݳ���
	char* BankId			in	��Կ֤���к�
	����ֵ
		0	�ɹ�
		����	ʧ��
*/				  
int UploadCertWithBankId(int sockFd, unsigned char* cert, int iCertLen, char* BankId);




/*
 *	5. HA �� �����ʽ �ϴ�֤��ָ���к�
	int  n					in	����HA��ʽ, �������˶��HA����, n��ʾ����ָ���ĵ�n������,ע�ⲻ�ǵڼ�̨, ���ǵڼ��ԡ���1��ʼ����
	unsigned char* cert		in	��Կ֤������(der���롢Base64����?)
	int iCertLen			in	��Կ֤�����ݳ���
	char *bankId			in	�к�
	int* status[]			out	�ϴ����, �����õ�����˳��һһ��Ӧ
	˵����
		(1) ʹ�ñ��ӿ�֮ǰֻ�����InitServerList��ʼ���������������GetConncetion
		(2) status�е�ֵ 0��ʾ�ɹ��ϴ�; ������ʾʧ��
		(3) status�е�״ֵ̬���������õ���������һ��
		(4) n ����ȡ���Ӵ���ֵһ��, ��������HA��ʽ����
	����
		0	�ɹ�		
		����	ʧ��
 */
int GroupUploadCertWithBankId(int n, unsigned char* cert, int iCertLen, char *bankId, int status[] );













/*-------------------------------------------ͬ����ֽӿ�-------------------------------------*/


/*	���ܼ��	ʮ�������ַ���ת�ڴ�����
	����˵��	
		char * HexStr����ʮ���������ݵ�ַ
		int HexStrLen����ʮ���������ݳ���
		char *Bin�����ڴ����ݵ�ַ
		int * BinLen�����ڴ����ݳ���
	����ֵ	int�C�����룬����0Ϊ�ɹ���������ʾʧ�ܣ��μ��������
*/
void HexStrToBin(char * HexStr, int HexStrLen, char *Bin, int *BinLen);


/*	���ܼ��	�ڴ�����תʮ�������ַ���
	����˵��	
		char *Bin�����ڴ����ݵ�ַ
		int BinLen�����ڴ����ݳ���
		char * HexStr����ʮ���������ݵ�ַ
		int * HexStrLen����ʮ���������ݳ���
	����ֵ	int�C�����룬����0Ϊ�ɹ���������ʾʧ�ܣ��μ��������
*/
void BinToHexStr(char *Bin, int BinLen, char * HexStr, int * HexStrLen);


/*	���ܼ��	����workingKey
	����˵��	
		int		sockFd�������Ӿ��
		char*	alg���������㷨��SM4/3DES
		unsigned char*	workingKey���������ƵĹ�����Կ
		int		keyLength����������Կ����
	����ֵ	int�C�����룬����0Ϊ�ɹ���������ʾʧ�ܣ��μ��������
*/
int setWorkingKey(int sockFd, char* alg, unsigned char* workingKey, int keyLength);



/*	���ܼ��	��֤checkcode
	����˵��	
		int		sockFd�������Ӿ��
		char*	alg���������㷨��SM4/3DES
		unsigned char*	workingKey���������ƵĹ�����Կ
		int		keyLength����������Կ����
		unsigned char *checkCode����  ��֤��
		int checkCodeLength����  ��֤�볤��
	����ֵ	int�C�����룬����0Ϊ�ɹ���������ʾʧ�ܣ��μ��������
*/
int setWorkingKeyWithCheckCode(int sockFd, char* alg, unsigned char* workingKey, int keyLength, unsigned char *checkCode, 
	int checkCodeLength);


/*	���ܼ��	����pPin����װ�ŷ�ӿڣ��÷��������õ�����Կ��pWorkingKeyʹ�÷��������õ��㷨���н��ܣ��ý��ܽ����Ϊ��Կ��ʹ��pDecPinAlg�㷨��PIN���н��ܣ��Խ��ܽ������pEncCertDN��ʹ��pEncAlg�㷨��װ�����ŷⲢ���ء�
	����˵��	
		int		sockFd�������Ӿ��
		unsigned char*	pPin�������ܺ��PIN�루�����ƣ�
		int		nPinLen�������ܺ��PIN�볤��
		char*	pDecPinAlg��������PIN����㷨
		char*	pEncCertDN�����ŷ����֤��������������
		char*	pEncAlg�����ŷ�����㷨
		unsigned char*	pB64Envelope�������ܳɹ�����Base64����������ŷ�
		int *	pnB64EnvelopeLen�������ܳɹ�����Base64����������ŷⳤ��
	����ֵ	int�C�����룬����0Ϊ�ɹ���������ʾʧ�ܣ��μ��������
*/
int DecPINAndEnvelope(int sockFd, unsigned char* pPin, int nPinLen, char* pDecPinAlg, 
	char* pEncCertDN, char* pEncAlg, unsigned char* pB64Envelope, int *pnB64EnvelopeLen);



/*	���ܼ��	���������ŷ⣬�õ�PIN������pEncCertDNָ���Ĺ�Կ��ʹ��pEncAlg�㷨��PIN�����ܣ��õ��µ������ŷ�
	����˵��	
		int		sockFd�������Ӿ��
		unsigned char*	pEnvelope���������ŷ⣨base64���룩
		int		nEnvelopeLen���������ŷⳤ�ȣ�base64���룩
		char*	pEncCertDN�����ŷ����֤��������������
		char*	pEncAlg�����ŷ�����㷨
		unsigned char*	pNewB64Envelope�����������ŷ⣨base64���룩
		int*	pnNewB64EnvelopeLen�����������ŷⳤ�ȣ�base64���룩
	����ֵ	int�C�����룬����0Ϊ�ɹ���������ʾʧ�ܣ��μ��������
*/
int RewrapEnvelope(int sockFd, unsigned char* pEnvelope, int nEnvelopeLen, char* pEncCertDN , 
	char* pEncAlg, unsigned char* pNewB64Envelope, int *pnNewB64EnvelopeLen);



/*	���ܼ��	���������ŷ⣬�õ�PIN�������������Ϊ������Կ���ù�����Կ����PIN��
	������Կ���ܹ�����Կ�����ؼ��ܺ��PIN�͹�����Կ
	����˵��	
		int		sockFd�������Ӿ��
		unsigned char*	pEnvelope���������ŷ⣨base64���룩
		int		nEnvelopeLen���������ŷⳤ�ȣ�base64���룩
		char*	encPinAlg��������PIN����㷨��DESede��
		unsigned char*	pEncPin�������ܺ�PIN��
		int*	pnEncPinLen�������ܺ�PIN�볤��
	����ֵ	int�C�����룬����0Ϊ�ɹ���������ʾʧ�ܣ��μ��������
*/
int DecEnvelopeAndEncPIN(int sockFd, unsigned char* pEnvelope, int nEnvelopeLen, 
	char* pEncPinAlg, unsigned char* pEncPin, int* pnEncPinLen);



/*	Dump���ɲ��Խӿڣ������ڲ�����ʹ�ã�*/
int DumpTest();


/*	�����쳣����������������ʱ����dump�ļ������Զ�λ*/
int SetDumpMachine();





/*1.	ָ��hash�㷨��ǩ��*/
int INS_RawSign(int sockFd, unsigned char* plain, int iPlainLen, char* signCertDN, 
	char* digestAlg, unsigned char* crypto,int* iCryptoLen);

/*2.	ʹ�ö�����֤���������ǩ*/
int INS_RAWVerify(int sockFd, unsigned char* crypto, int iCryptoLen, unsigned char* plain, 
	int iPlainLen, char* digestAlg, unsigned char* cert, int iCertLen, CERTINFO *cinfo);

/*3.	ʹ�ö�����֤���º���ǩ*/
int INS_RAWAfterwardsVerify (int sockFd, unsigned char *crypto, int iCryptoLen, 
	unsigned char* plain, int iPlainLen, char* digestAlg, unsigned char* cert, 
	int iCertLen, CERTINFO *cinfo);

/*4.	��ϣ����ǩ*/
int DigestVerify(int sockFd, unsigned char* hash, int iHashLen, unsigned char* crypto, 
	int iCryptoLen, unsigned char* cert, int iCertLen, CERTINFO *cinfo);


/*5.	ָ��hash�㷨��Detachedǩ��*/
int INS_DetachedSign(int sockFd, unsigned char* plain, int iPlainLen, char* signCertDN,	
	char* digestAlg, unsigned char* crypto, int* iCryptoLen);

/*6.	Detached��ǩ*/
int INS_DetachedVerify(int sockFd, unsigned char* crypto, int iCryptoLen, 
	unsigned char* plain, int iPlainLen, int iReturnCert, CERTINFO *cinfo);

/*7.	Detached�º���ǩ*/
int INS_DetachedAfterwardsVerify(int sockFd, unsigned char* crypto, int iCryptoLen, 
	unsigned char* plain, int iPlainLen, int iReturnCert, CERTINFO *cinfo);


/*8.	ָ��hash�㷨��Attachedǩ��*/
int INS_AttachedSign(int sockFd, unsigned char* plain, int iPlainLen, char* signCertDN,
	char* digestAlg, unsigned char* crypto, int* iCryptoLen );

/*9.	Attached��ǩ*/
int INS_AttachedVerify(int sockFd, unsigned char* crypto, int iCryptoLen, int iReturnCert,
	unsigned char* plain, int *iPlainLen, CERTINFO *cinfo);

/*10.	Attached�º���ǩ*/
int INS_AttachedAfterwardsVerify(int sockFd, unsigned char *crypto, int iCryptoLen, 
	int iReturnCert, unsigned char* plain, int *iPlainLen, CERTINFO *cinfo);


/*11.	���������ŷ�*/
int INS_EncryptEnvelope(int sockFd, unsigned char* plain, int iPlainLen, 
	unsigned char* enCert, int iEnCertLen, unsigned char* crypto, int* iCryptoLen);

/*12.	���������ŷ�*/
int INS_DecryptEnvelop(int sockFd, unsigned char* crypto, int iCryptoLen, char* enCertDN,
	unsigned char* plain, int* iPlainLen, CERTINFO *cinfo);


/*13.	ǩ���������ŷ�*/
int INS_SignAndEncryptEnvelope(int sockFd, unsigned char* plain, int iPlainLen, 
	char* signCertDN, char* enCertDN, unsigned char* crypto, int* iCryptoLen );

/*14.	�������ŷⲢ��ǩ��*/
int INS_DecryptedAndVerifiedEnvelop(int sockFd, unsigned char* crypto, int iCryptoLen,
	char* enCertDN, char* plain, int* iPlainLen, CERTINFO *sinfo, CERTINFO *einfo);

/*15.	PDFǩ��*/
int INS_PDFSign(int sockFd, unsigned char* pdf, int iPdfLen, char* signCertDN, 
	unsigned char* crypto, int *iCryptoLen, PDF_SIGN_PARAM *param);

/*15.1	PDFǩ��(����ָ��hash�㷨)*/
int INS_PDFSignWithHash(int sockFd, unsigned char* pdf, int iPdfLen, 
						char* signCertDN, char* hashAlg,
				unsigned char* crypto, int *iCryptoLen, PDF_SIGN_PARAM *param);
/*15.1	PDFǩ��(ʹ���ⲿ�����֤������pfx�ļ�)*/
int INS_PDFSignWithPfx(int sockFd, unsigned char* pdf, int iPdfLen, 
					   unsigned char* pfxcert, int pfxLen, char* pfxpwd, char *hashALg,
					   unsigned char* crypto, int *iCryptoLen, PDF_SIGN_PARAM *param);

/*16.	PDF��ǩ*/
int INS_PDFVerify(int sockFd, unsigned char* pdf, int iPdfLen, char* password, 
	int iReturnCert, CERTINFO* result);

/*16.	PDF��ǩ(��ǩ�µ���֤)*/
int INS_PDFMultiVerify(int sockFd, unsigned char* pdf, int iPdfLen, char* password, 
					   int isRetCert, PDFVerifyRet verifyResult[], int *nResultCnt);

/*17.	�Ƹ�ͨǩ��*/
int INS_TenPaySign(int sockFd, unsigned char* xml, int iXmlLen, char* signCertDN, 
	char * sReqID, unsigned char* crypto, int *iCryptoLen);

/*18.	�Ƹ�ͨ��ǩ*/
int INS_TenPayVerify(int sockFd, unsigned char* xml, int iXmlLen, 
	unsigned char* cert, int iCertLen, CERTINFO *cinfo);


/*19.	֧����ǩ��*/
int INS_AlipaySign(int sockFd, unsigned char* xml, int iXmlLen, char* signCertDN , 
	unsigned char* crypto, int *iCryptoLen );

/*20.	֧������ǩ*/
int INS_AlipayVerify(int sockFd, unsigned char* xml, int iXmlLen, 
	unsigned char* cert, int iCertLen, CERTINFO *cinfo);

/*21.	����39����*/
int INS_GenBarCode39(int sockFd, unsigned char* plain, int iPlainLen, int addCheckSUM, 
	float wideFactor, int displayStartStop, BAR_CODE_PARAM param, unsigned char* image,
	int* imageLen);

/*22.	����128����*/
int INS_GenBarCode128(int sockFd, unsigned char* plain, int iPlainLen, BAR_CODE_PARAM param,
	unsigned char* image, int* imageLen);

/*23.	���ɽ���25����*/
int INS_GenBarCodeInter25(int sockFd, unsigned char* plain, int iPlainLen, int addCheckSUM,
	float wideFactor, BAR_CODE_PARAM param, unsigned char* image, int* imageLen);

/*24.	���ɿ�°�����*/
int INS_GenBarCodeCodabar(int sockFd, unsigned char* plain, int iPlainLen, float wideFactor,
	int displayStartStop, BAR_CODE_PARAM param, unsigned char* image, int* imageLen);

/*25.	����417����*/
int INS_GenBarCode417(int sockFd, unsigned char* plain, int iPlainLen, int errorCorrectLevel,
	float aspectRatio, float yHeight, int imgFormat, unsigned char* image, int *imageLen);

/*26.	���ɿ�����Ӧ��*/
int INS_GenBarCodeQRCode(int sockFd, unsigned char* plain, int iPlainLen, int encodeMode,
	int errorCorrectLevel, int barSize, int imgFormat, unsigned char* image, int *imageLen);



/**************************************************************************************/
/******************************�����޿�֧���ӿ�API**************************************/
/**************************************************************************************/

/* 
 * �����޿�֧���ӿ�
 * 1.	rawǩ��
 *
 int sockFd					in	ǩ�����������Ӿ��
 char* szCertDN				in	ǩ��֤���ʶ��DN(����)���к�
 unsigned char* pData		in	��ǩ������ԭ��
 int iDataLen				in	��ǩ��ԭ�ĳ���
 char* digestAlg			in  ժҪ�㷨��0��SHA256,1��SM3
 char *pSignature			out	����ǩ��ֵ�Ļ�����,ʹ��RSA֤��ʱ���ٷ���350�ֽڣ�ʹ��SM2֤��ʱ���ٷ���90�ֽڡ�ǩ���ɹ��󣬷���base64�ַ�����


����ֵ��
�ɹ�,����0
����	ʧ��,���ش�����

˵��:
��
*/
int CUPNCPRawSign(int sockFd, char* szCertDN, 
				  unsigned char* pData, int iDataLen, char* digestAlg,
				  char *pSignature );


/* 
 * �����޿�֧���ӿ�
 * 2.	raw��֤ǩ��
 *
 int sockFd					in	ǩ�����������Ӿ��
 char* szCertDN				in	ǩ��֤���ʶ��DN(����)���к�
 unsigned char* pData		in	��ǩ������ԭ��
 int iDataLen				in	��ǩ��ԭ�ĳ���
 char* digestAlg			in  ժҪ�㷨��0��SHA256,1��SM3
 char *pSignature			in	ǩ��ֵ(base64����)���������Ϊ�ַ���


����ֵ��
�ɹ�,����0
����	ʧ��,���ش�����

˵��:


*/
int CUPNCPRawVerify(int sockFd, char* szCertDN, 
					unsigned char* pData,int iDataLen, char* digestAlg,
					char *pSignature);


/* 
 * �����޿�֧���ӿ�
 * 3.	����
 *
int sockFd						in	ǩ�����������Ӿ��
char* szCertDN					in	ǩ��֤���ʶ��DN(����)���к�
unsigned char* pData			in	������Ϣ��������
int iDataLen					in	�������ݳ���
char* symmAlg					in	�ԳƼ����㷨��0��3DES��1��SM4
char* encryptedKey				out ���ؼ�����Կ�Ļ�������ʹ��RSA֤��ʱ���ٷ���350�ֽڣ�ʹ��SM2֤��ʱ���ٷ���160�ֽڡ����ܳɹ��󣬷���base64�ַ�����
char *pEncryptedData			out	����������Ϣ���ĵĻ���������������С����Ϊ��(�������ݳ���+16)*4/3���ֽڡ����ܳɹ��󣬷���base64�ַ�����


����ֵ��
�ɹ�,����0
����	ʧ��,���ش�����

˵��:

*/
int CUPNCPEncrypt(int sockFd, char* szCertDN, 
				  unsigned char* pData, int iDataLen, 
				  char* symmAlg , char* encryptedKey , 
				  char *pEncryptedData );




/* 
 * �����޿�֧���ӿ�
 * 4.	����
 *
 int sockFd						in	ǩ�����������Ӿ��
 char* szCertDN					in	ǩ��֤���ʶ��DN(����)���к�
char* encryptedKey				in	�Գ���Կ����(base64����)���������Ϊ�ַ���
char* encryptedData				in  ������Ϣ��������(base64����)���������Ϊ�ַ���
char* symmAlg					in	�ԳƼ����㷨���ԳƼ����㷨��0��3DES��1��SM4
unsigned char* pData			out	����������Ϣ�������ݵĻ�������������䳤��Ϊ��������Ϣ���ĳ���*3/4+5��
int *piDataLen					in/out	��������������ݵĻ�������󳤶�,����ʵ�ʽ����������ݵĳ���

����ֵ��
�ɹ�,����0
����	ʧ��,���ش�����

˵��:

*/
int CUPNCPDecrypt(int sockFd, char* szCertDN,
				  char* encryptedKey , char *encryptedData, char* symmAlg ,
				  unsigned char* pData, int *piDataLen);



/**************************************************************************************/
/******************************����ɨ��֧���ӿ�API**************************************/
/**************************************************************************************/

/* 
 * ����ɨ��֧���ӿ�
 * 1.	rawǩ��
 *
 int sockFd					in	ǩ�����������Ӿ��
 char* szCertDN				in	ǩ��֤���ʶ��DN(����)���к�
 unsigned char* pData		in	��ǩ������ԭ��
 int iDataLen				in	��ǩ��ԭ�ĳ���
 char* digestAlg			in  ժҪ�㷨��SHA1
 char *pSignature			out	����ǩ��ֵ�Ļ�����,ʹ��RSA֤��ʱ���ٷ���350�ֽڣ�ʹ��SM2֤��ʱ���ٷ���90�ֽڡ�ǩ���ɹ��󣬷���base64�ַ�����


����ֵ��
�ɹ�,����0
����	ʧ��,���ش�����

˵��:
��
*/
int CUPBCPRawSign(int sockFd, char* szCertDN, 
				  unsigned char* pData, int iDataLen, char* digestAlg,
				  char *pSignature );


/* 
 * ����ɨ��֧���ӿ�
 * 2.	raw��֤ǩ��
 *
 int sockFd					in	ǩ�����������Ӿ��
 char* szCertDN				in	ǩ��֤���ʶ��DN(����)���к�
 unsigned char* pData		in	��ǩ������ԭ��
 int iDataLen				in	��ǩ��ԭ�ĳ���
 char* digestAlg			in  ժҪ�㷨����sha1��
 char *pSignature			in	ǩ��ֵ(base64����)���������Ϊ�ַ���


����ֵ��
�ɹ�,����0
����	ʧ��,���ش�����

˵��:


*/
int CUPBCPRawVerify(int sockFd, char* szCertDN, 
					unsigned char* pData,int iDataLen, char* digestAlg,
					unsigned char *pSignature);


/* 
 * ����ɨ��֧���ӿ�
 * 3.	����
 *
int sockFd						in	ǩ�����������Ӿ��
char* szCertDN					in	ǩ��֤���ʶ��DN(����)���к�
unsigned char* pData			in	������Ϣ��������
int iDataLen					in	�������ݳ���
char *pEncryptedData			out	����������Ϣ���ĵĻ���������������С����Ϊ350�ֽڡ����ܳɹ��󣬷���base64�ַ�����


����ֵ��
�ɹ�,����0
����	ʧ��,���ش�����

˵��:

*/
int CUPBCPEncrypt(int sockFd, char* szCertDN, 
				  unsigned char* pData, int iDataLen, 
				  char *pEncryptedData );




/* 
 * ����ɨ��֧���ӿ�
 * 4.	����
 *
 int sockFd						in	ǩ�����������Ӿ��
 char* szCertDN					in	ǩ��֤���ʶ��DN(����)���к�
char* encryptedData				in  ������Ϣ��������(base64����)���������Ϊ�ַ���
unsigned char* pData			out	����������Ϣ�������ݵĻ�������������䳤������Կ����һ��128/256
int *piDataLen					in/out	��������������ݵĻ�������󳤶�,����ʵ�ʽ����������ݵĳ���

����ֵ��
�ɹ�,����0
����	ʧ��,���ش�����

˵��:

*/
int CUPBCPDecrypt(int sockFd, char* szCertDN, char *encryptedData,  
				  unsigned char* pData, int *piDataLen);




/**************************************************************************************/
/******************************�������װ�����ŷ�ӿ�************************************/
/**************************************************************************************/

/* 
 * 1.	���������
 *
int sockFd						in	ǩ�����������Ӿ��
int randomLen					in	�����byte����
char* symmAlg					in  �����ŷ�ԳƼ����㷨 DES/DESEde/AES/RC4/SM4����������ΪNULL�����÷�����Ĭ���㷨
char* szCertDN					in	����֤���ʶ��DN(����)���к�
unsigned char *enccert			in	����֤��(DER����)
int enccertlen					in	����֤�鳤��
unsigned char *outRandomEnvelope out ���������ŷ�
int *outEnvelopeLen				in/out �������outRandomEnvelope������ڴ��С�� ��� �����ŷ��ʵ�ʳ���
int iscipher					in  �Ƿ�ʹ�ù�Կ���ܱ�������������
unsigned char *pubkey			in	�ͻ��˹�Կ(DER����)
int pubLen						in	�ͻ��˹�Կ����
unsigned char *outRandom		out	�������������
int *outRandomLen				in/out �������outRandomEnvelope������ڴ��С�� ��� �����ŷ��ʵ�ʳ���



����ֵ��
�ɹ�,����0
����	ʧ��,���ش�����

˵��:
1 iscipher != 0,pubkey = 0 �����ص������outRandomΪ�������
2 outRandom = 0��������������
3 szCertDN �� [enccert�� enccertlen]����������� ��ѡһ��
*/
int INS_GenRandomEnvelope(int sockFd, int randomLen, char* symmAlg, 
						  char* szCertDN,  unsigned char* enccert , int enccertlen,
						  unsigned char *outRandomEnvelope, int *outEnvelopeLen,
						  int iscipher,  unsigned char *pubkey, int pubLen,
						  unsigned char *outRandom, int *outRandomLen);


/* 
 * 2.	������������ŷ��ʽת��Ϊ��һ�鹫Կ���ܸ�ʽ��
 *
int sockFd						in	ǩ�����������Ӿ��
char* symmAlg					in  �����ŷ�ԳƼ����㷨 DES/DESEde/AES/RC4/SM4����������ΪNULL�����÷�����Ĭ���㷨
char* szCertDN					in	����֤���ʶ��DN(����)���к�
unsigned char *enccert			in	����֤��(DER����)
int enccertlen					in	����֤�鳤��
unsigned char *pubkey			in	�ͻ��˹�Կ(DER����)
int pubLen						in	�ͻ��˹�Կ����
unsigned char *RandomEnvelope	in	�����ŷ�
int EnvelopeLen					in  �����ŷ��ʵ�ʳ���
unsigned char *outRandom		out	������������ݣ����Ļ�ͻ��˹�Կ���ܱ�����
int *outRandomLen				in/out �������outRandom������ڴ��С�� ��� ���������������ģ���ʵ�ʳ���

����ֵ��
�ɹ�,����0
����	ʧ��,���ش�����

˵��:
1 szCertDN ,[enccert�� enccertlen],[pubkey, publen] ����������� ����ѡһ
2 ����������������ΪNULL���������

*/
int INS_RewarpEnvelope(int sockFd, char* symmAlg,
					   char* szCertDN,unsigned char* enccert , int certlen,
					   unsigned char *pubkey, int pubLen,
					   unsigned char *RandomEnvelope, int EnvelopeLen,
					   unsigned char *outRandom, int *outRandomLen);

/*
        ---------------------------------------------------------WangLianAPI Start ---------------------------------------------------------------------------------
*/
int WangLianEnc(int sockFd, unsigned char* plain, int iTotlenum, int iPlainlenserial[], 
				char* SN, char* Alg, unsigned char* crypto, int iCryptolenserial[], unsigned char* cryptoEnv, int* pCryptoenvlen);

int WangLianDec(int sockFd, unsigned char* crypto, int iTotlenum, int iCryptolenserial[], 
				unsigned char* cryptoEnv, int iCryptoenvlen, char* SN, char* Alg, unsigned char* plain, int iPlainlenserial[]);


int WangLianFileEnc(int sockFd, char* plain_file_path, char* SN, char* Alg, 
					char* cipher_file_path, unsigned char* cryptoEnv, int* pCryptoenvlen);

int WangLianFileDec(int sockFd, char* cipher_file_path, unsigned char* cryptoEnv, int iCryptoEnvlen, char* SN, char* plain_file_path);

/*
        ---------------------------------------------------------BCM API ---------------------------------------------------------------------------------
*/
int INS_DetachedSign_BCM(int sockFd, unsigned char* plain,int iPlainLen, char* signCertDN, char* digestAlg, unsigned char* crypto, int* iCryptoLen);

int INS_DetachedVerify_BCM(int sockFd, unsigned char* crypto, int iCryptoLen, unsigned char* plain, int iPlainLen, int iReturnCert, CERTINFO *cinfo, CERTINFOEXT *cert_info_ext, char *pDataSignAlg);

int INS_RawSign_BCM(int sockFd, unsigned char* plain, int iPlainLen, char* signCertDN, char* digestAlg, unsigned char* crypto, int* iCryptoLen);

int INS_RawVerify_BCM(int sockFd, unsigned char* crypto, int iCryptoLen, unsigned char* plain, int iPlainLen, char* digestAlg, unsigned char* cert, int iCertLen, CERTINFO *cinfo, CERTINFOEXT *cert_info_ext, char *pDataSignAlg);

int RawSign_BCM(int sockFd, unsigned char* plain, int iPlainLen, char* signCertDN, unsigned char* crypto, int* iCryptoLen);

int RawVerify_BCM(int sockFd, unsigned char* plain, int iPlainLen, char* signCertDN, unsigned char* crypto, int iCryptoLen, int iCertOper, CERTINFO *cinfo, CERTINFOEXT *cert_info_ext, char *pDataSignAlg);

int INS_RAWAfterwardsVerify_BCM(int sockFd,unsigned char* plain, int iPlainLen,unsigned char *crypto, int iCryptoLen,char* digestAlg, unsigned char* cert, int iCertLen, CERTINFO *cinfo, CERTINFOEXT *cert_info_ext, char *pDataSignAlg);

int DetachedSign_BCM(int sockFd, unsigned char* plain, int iPlainLen, char* signCertDN, unsigned char* crypto, int* iCryptoLen );


int DetachedVerify_BCM(int sockFd, unsigned char* plain, int iPlainLen, unsigned char* crypto, int iCryptoLen, int bRetCert, CERTINFO *cinfoi, CERTINFOEXT *cert_info_ext, char *pDataSignAlg);

int CheckAllNetsignStatus(char list[][100], int len,int status[] );

int PCACDecrypt(int sockFd, unsigned char* crypto, int iTotlenum, int iCryptolenserial[], unsigned char* cryptoEnv, int iCryptoenvlen, char* SN, char* Alg, unsigned char* plain, int iPlainlenserial[]);

int PCACEncrypt(int sockFd, unsigned char* plain, int iTotlenum, int iPlainlenserial[], char* SN, char* Alg, unsigned char* crypto, int iCryptolenserial[], unsigned char* cryptoEnv, int* pCryptoenvlen);

int RawSignHash(int sockFd,unsigned char* hash, int iHashLen, char *digestAlg, char *signCertDN, unsigned char* crypto, int *iCryptoLen);

int RawVerifyHash(int sockFd,unsigned char* hash, int iHashLen, char *digestAlg, char *signCertDN, unsigned char* crypto, int iCryptoLen, CERTINFO *cinfo);

int CheckAllOperateCard(char list[][100], int len, char status[][100] );


/*
        ---------------------------------------------------------XML Sign API---------------------------------------------------------------------------------
*/

#define INS_CANONICALTYPE_XML10 "http://www.w3.org/TR/2001/REC-xml-c14n-20010315"
/*not support: #define INS_CANONICALTYPE_XML11  "http://www.w3.org/2006/12/xml-c14n11"*/
#define INS_CANONICALTYPE_EXCLUSIVE10  "http://www.w3.org/2001/10/xml-exc-c14n#"
#define INS_CANONICALTYPE_XML10_COMMENTS  "http://www.w3.org/TR/2001/REC-xml-c14n-20010315#WithComments"
/*not support: #define INS_CANONICALTYPE_XML11_COMMENTS  "http://www.w3.org/2006/12/xml-c14n11#WithComments"*/
#define INS_CANONICALTYPE_EXCLUSIVE10_COMMENTS  "http://www.w3.org/2001/10/xml-exc-c14n#WithComments"

/*XML��Ƥǩ��*/
int INS_XMLEnvelopedSign(int sockFd, 
						 unsigned char* xml, int iXmlLen, char * canonicalType,
						 char* signCertDN, char *digestAlg, char* sigID, 
						 unsigned char* crypto, int* iCryptoLen);
/*XML����ǩ��*/
int INS_XMLEnvelopingSign(int sockFd, 
						  unsigned char* xml, int iXmlLen, char * canonicalType,
						  char* signCertDN, char *digestAlg, char* sigID, 
						  unsigned char* crypto, int* iCryptoLen);
/*XML����ǩ��*/
int INS_XMLDetachedSign(int sockFd, 
						unsigned char* xml, int iXmlLen, char * canonicalType,
						char* signCertDN, char *digestAlg, char* sigID,char *tbsID, 
						unsigned char* crypto, int* iCryptoLen);
/*XML��ǩ��*/
int INS_XMLVerifySign(int sockFd, 
					  unsigned char* crypto, int iCryptoLen, 
					  int isReturnCert, XMLVerifyRet verifyResult[], int *nResultCnt);

/*XML��ǩ��(with cert)*/
int INS_XMLVerifyByCert(int sockFd, 
					  unsigned char* crypto, int iCryptoLen, 
					  unsigned char* x509cert, int x509Len, 
					  XMLVerifyRet verifyResult[], int *nResultCnt);

/*XML����ǩ��*/
int INS_XMLChinaPortSign(int sockFd, 
						unsigned char* xml, int iXmlLen, char* signCertDN, 
						char* sigID, char *tbsID, char *keyName, int isContainCert,
						unsigned char* crypto, int* iCryptoLen);
/*
        ---------------------------------------------------------BANK 2,3 type Sign API---------------------------------------------------------------------------------
*/

/* �������Ĺ�����Կ
	int sockFd					in	ǩ�����������Ӿ��
	int keytype					in	������Կ���ͣ�Ŀǰ֧��2�� 1  
	unsigned char* workingkey	in	������Կֵ
	int iKeylen					in	������Կ����
	����ֵ
		0	�ɹ�
		����	ʧ��
˵��:
(1) ������Կ�ĸ�ʽ�Ƕ�����
(2) Ŀǰ��Կ������3DES�� ��Կ����ֻ���� 16�� 24�ֽڣ�����������Ч;
*/

#define CUPPTC_KEYTYPE_PIN			1
#define CUPPTC_KEYTYPE_TRANS		3

int CUPSTCSetWorkingKey(int sockFd, int keytype, unsigned char* workingkey, int iKeylen);


/*����ǩ��*/
int CUPSTCRawSign(int sockFd, unsigned char* plain, int plainLen, char* signCertDN, char *digestAlg, unsigned char* crypto, int* iCryptoLen);
/*��֤ǩ��*/
int CUPSTCRawVerify(int sockFd, unsigned char* plain, int plainLen, char* signCertDN, char *digestAlg, unsigned char* crypto, int iCryptoLen);
/*��֤ǩ����with cert��*/
int CUPSTCRawVerifyWithCert(int sockFd, unsigned char* plain, int plainLen, unsigned char* Cert, int nCertLen, char *digestAlg, unsigned char* crypto, int iCryptoLen);
/*��ͨ���ļ���
������ ԭ�ĸ�ʽ��� �����ǣ�
 1 ���ĸ�ʽӦ���� json��ʽ��'{'��Ϊ����ĸ��
 2 �������json��ʽ��ֻ�����Ǹ���ʶ����(pin)�ļ��� ��ԭ�ĳ��ȱ����� 8�ֽڣ�*/
int CUPSTCEncrypt(int sockFd, unsigned char* plain, int plainLen, int keytype, unsigned char* crypto, int* iCryptoLen);


/*��ͨ���Ľ���*/
int CUPSTCDecrypt(int sockFd, unsigned char* crypto, int iCryptoLen, int keytype, unsigned char* plain, int *plainLen);


/*������Կ���ļ���*/
int CUPSTCEncryptWorkingKey(int sockFd, unsigned char* workingkey, int iKeyLen, char* encCertDN, unsigned char* crypto, int* iCryptoLen);
/*������Կ���Ľ���*/
int CUPSTCDecryptWorkingKey(int sockFd, unsigned char* crypto, int iCryptoLen, char* encCertDN, unsigned char* workingkey, int *iKeyLen);



/*��������������ʱ��ʵ��
 ����&ǩ��
 int CUPSTCEncryptAndSign(int sockFd, char *jsonMsg, char *encCertDN, char *signCertDN, unsigned char* crypto, int* iCryptoLen);
 ����&��ǩ
 int CUPSTCDecryptAndVerify(int sockFd, char *jsonMsg, char *encCertDN, char *signCertDN);*/
/*
��Ϊ��Щ��Ŀ��Ҫ֧�ֶ�����ˣ����������Կ��Ϊ�˱��ֽӿ��ȶ�������ԭ�нӿڶ����޸ģ�
ʹ���µĺ��������������б仯�����ԭ�к���.��ԭ�к��������м���� "Msg"��ʾ����

*/

/*���������궨����netsign������������Ԥ����ֵ��
 ��ԭ�� CUPSTCEncrypt�� CUPSTCDecrypt�� CUPSTCSetWorkingKey ������ ���� [int keytype] ����� 1 �� 3 ��
 �ֱ��Ӧ�±߶���� CUPPTC_KEYTYPE_PIN_LABEL, CUPPTC_KEYTYPE_TRANS_LABEL,
 ע�⣺����Ŀ�ľ����븲��ԭ���ӿڵ�PIN �ʹ�����Կ������Ҫʹ��������ֵ��*/

/*CUPPTC_KEYTYPE_PIN_LABEL �ڲ��������� CUPPTC_KEYTYPE_PIN��1������Ӧ����Կ
  CUPPTC_KEYTYPE_TRANS_LABEL �ڲ��������� CUPPTC_KEYTYPE_TRANS��3������Ӧ����Կ */
#define	CUPPTC_KEYTYPE_PIN_LABEL	"cupstcpinkey"
#define CUPPTC_KEYTYPE_TRANS_LABEL "cupstctranskey"

/* �������Ĺ�����Կ(��� CUPSTCSetWorkingKey)
	int sockFd					in	ǩ�����������Ӿ��
	char* keyLabel				in	������Կ�ı�ʶ
	unsigned char* workingkey	in	������Կֵ
	int iKeylen					in	������Կ����
	����ֵ
		0	�ɹ�
		����	ʧ��
˵��:
(1) keyLabel �ǹ�����Կ�Ĵ洢��ʹ�õı�ʶ��Ӧ���Լ����ж�������ʶ������ƣ���󳤶�����32���ֽ�;
(2) ������Կ�ĸ�ʽ�Ƕ�����
(3) Ŀǰ��Կ������3DES�� ��Կ����ֻ���� 16�� 24�ֽڣ�����������Ч;
*/
int CUPSTCMsgSetWorkingKey(int sockFd, char* keyLabel, unsigned char* workingkey, int iKeylen);

/*��ͨ���ļ���(��� CUPSTCEncrypt )*/
int CUPSTCMsgEncrypt(int sockFd, unsigned char* plain, int plainLen, char* keyLabel, unsigned char* crypto, int* iCryptoLen);

/*��ͨ���Ľ���(��� CUPSTCDecrypt)*/
int CUPSTCMsgDecrypt(int sockFd, unsigned char* crypto, int iCryptoLen, char* keyLabel, unsigned char* plain, int *plainLen);


/*���ܲ����ù�����Կ*/
int CUPSTCDecryptResetWorkingKey(int sockFd, unsigned char* crypto, int iCryptoLen, char *encCertDN, char* keyLabel, int *keytype);



/*
��Լ��ܣ����ܣ�ǩ������֤��hash�㷨�Ȼ��������Ľӿ�
*/

/* 1.	raw sign

	����˵��
		int sockFd				in		socket ���
		unsigned char* data		in		��ǩ�����ݣ������ƣ�
		int iLen				in		��ǩ�����ݳ���
		char* signCertDN		in		ǩ��֤��DN���кţ����Ϊnull��ʹ�÷�����Ĭ��֤�飩
		char *digestAlg			in		ǩ����hash�㷨�����Ϊnull��ʹ�÷�����Ĭ���㷨��
		int flag				in		ǩ������Ĳ�λģʽ���˴�Ĭ����дΪ 0x00 (sign data), 0x10 sign hash, 0x20 No Padding(only for rsa)
		unsigned char* crypto	out		ǩ������������ƣ��ⲿ��������ڴ棩
		int* iCryptoLen			in/out	ǩ��������ȣ�����ǩ�����crypto����������󳤶ȣ����ʵ�ʵ�ǩ��������ȣ�
	
	˵��:
			��
	����ֵ
		0�ɹ�		��0ʧ��

 */
int INS_RawSignData(int sockFd, unsigned char* data, int iLen, 
				char* signCertDN, char *digestAlg, int flag, 
				unsigned char* crypto, int* iCryptoLen);



/* 2.	raw verify

	����˵��
		int sockFd				in		socket ���
		unsigned char* data		in		��ǩ�����ݣ������ƣ�
		int iLen				in		��ǩ�����ݳ���
		char* signCertDN		in		ǩ��֤��DN���кţ����Ϊnull��ʹ�÷�����Ĭ��֤�飩
		char *digestAlg			in		ǩ����hash�㷨�����Ϊnull��ʹ�÷�����Ĭ���㷨��
		int flag				in		�˴�Ĭ����дΪ 0x00 (sign data), 0x10 sign hash, 0x20 No Padding(only for rsa)
		unsigned char* crypto	in		ǩ������������ƣ�
		int iCryptoLen			in		ǩ���������
	
	˵��:
			��
	����ֵ
		0�ɹ�		��0ʧ��

 */
int INS_RawVerifyData(int sockFd, unsigned char* data, int iLen, 
				  char* signCertDN, char *digestAlg, int flag, 
				  unsigned char* crypto, int iCryptoLen);

/* 3.	raw verify(with cert)

	����˵��
		int sockFd				in		socket ���
		unsigned char* data		in		��ǩ�����ݣ������ƣ�
		int iLen				in		��ǩ�����ݳ���
		unsigned char* x509cert	in		ǩ��֤��
		int x509Len				in		ǩ��֤�鳤��
		char *digestAlg			in		ǩ����hash�㷨�����Ϊnull��ʹ�÷�����Ĭ���㷨��
		int flag				in		�˴�Ĭ����дΪ 0x00 (sign data), 0x10 sign hash, 0x20 No Padding(only for rsa)
		unsigned char* crypto	in		ǩ������������ƣ�
		int iCryptoLen			in		ǩ���������
	
	˵��:
			��
	����ֵ
		0�ɹ�		��0ʧ��

 */
int INS_RawVerifyWithCert(int sockFd, unsigned char* data, int iLen, 
					  unsigned char* x509cert, int x509Len, char *digestAlg, int flag, 
					  unsigned char* crypto, int iCryptoLen);

/* 4.	pubkey encrypt

	����˵��
		int sockFd				in		socket ���
		unsigned char* data		in		������ԭ�ģ������ƣ�
		int iLen				in		������ԭ�ĳ���
		char* signCertDN		in		����֤��DN���кţ����Ϊnull��ʹ�÷�����Ĭ��֤�飩
		int flag				in		���ܵĲ�λģʽ���˴���дΪ 0���������������Ժ�����ʹ�ã�
		unsigned char* crypto	out		���ܽ���������ƣ�
		int* iCryptoLen			in/out	���ܽ������
	
	˵��:
			��
	����ֵ
		0�ɹ�		��0ʧ��

 */
int INS_RawEncrypt(int sockFd, unsigned char* data, int iLen, 
				   char* encCertDN, int flag, 
				   unsigned char* crypto, int* iCryptoLen);

/* 5.	pubkey encrypt��with cert��

	����˵��
		int sockFd				in		socket ���
		unsigned char* data		in		������ԭ�ģ������ƣ�
		int iLen				in		������ԭ�ĳ���
		unsigned char* x509cert	in		����֤��
		int x509Len				in		����֤�鳤��
		int flag				in		���ܵĲ�λģʽ���˴���дΪ 0���������������Ժ�����ʹ�ã�
		unsigned char* crypto	out		���ܽ���������ƣ�
		int* iCryptoLen			in/out	���ܽ������
	
	˵��:
			��
	����ֵ
		0�ɹ�		��0ʧ��

 */
int INS_RawEncryptWithCert(int sockFd, unsigned char* data, int iLen, 
				   unsigned char* x509cert, int x509Len, int flag, 
				   unsigned char* crypto, int* iCryptoLen);

/* 6.	pubkey decrypt

	����˵��
		int sockFd				in		socket ���
		unsigned char* crypto	in		�������ģ������ƣ�
		int* iCryptoLen			in		�������ĳ���
		char* encCertDN			in		����֤��DN���кţ����Ϊnull��ʹ�÷�����Ĭ��֤�飩
		int flag				in		���ܵĲ�λģʽ���˴���дΪ 0���������������Ժ�����ʹ�ã�
		unsigned char* data		out		���ܺ�ԭ�ģ������ƣ�
		int iLen				in/out	���ܺ�ԭ�ĳ���
	
	˵��:
			��
	����ֵ
		0�ɹ�		��0ʧ��

 */
int INS_RawDecrypt(int sockFd,unsigned char* crypto, int iCryptoLen, 
				   char* encCertDN, int flag, 
				   unsigned char* data, int *iLen );


/* 7.	import session key

	����˵��
		int sockFd				in		socket ���
		char* KeyType			in		��Կ���� DES��3DES��AES,SM4...
		char *szkeyID			in		��ԿID��Ψһ��ʶ��
		unsigned char* key		in		��Կ�������ƣ�
		int iLen				in		��Կ���ȣ�byte �ֽڳ��ȣ�
	
	˵��:
			��
	����ֵ
		0�ɹ�		��0ʧ��

 */


int INS_SetSessionKey(int sockFd, char* KeyType, char *szkeyID, unsigned char* key, int iLen );

/* 8.	import session key��pubkey encrypt��

	����˵��
		int sockFd				in		socket ���
		char* encCertDN			in		����֤��DN���кţ����Ϊnull��ʹ�÷�����Ĭ��֤�飩
		char* KeyType			in		��Կ���� DES��3DES��AES,SM4...
		char *szkeyID			in		��ԿID��Ψһ��ʶ��
		unsigned char* wrappedKey in	��Կ�����ģ������ƣ�
		int wrapedKeyLen		in		��Կ���ȣ�byte �ֽڳ��ȣ�
	
	˵��:
			��
	����ֵ
		0�ɹ�		��0ʧ��

 */


int INS_ImportSessionKey(int sockFd, char* encCertDN, char* KeyType, char *szkeyID, unsigned char* wrappedKey, int wrapedKeyLen );

/* 8.	import session key��session key encrypt��

	����˵��
		int sockFd						in		socket ���
		char* keyID						in		�Գ���Կ key label(ID,Ψһ��ʶ��
		SymmEncryptParam *decKeyParam	in		�ԳƼ��ܲ��� (ģʽ��IV��)
		char* importKeyType				in		Ҫ�������Կ���� DES��3DES��AES,SM4...
		char *szImportKeyID				in		Ҫ�������Կkey label (ID,Ψһ��ʶ��
		unsigned char* wrappedKey		in		Ҫ�������Կֵ�����ģ������ƣ�
		int wrapedKeyLen				in		Ҫ�������Կֵ���ȣ�byte �ֽڳ��ȣ�
	
	˵��:
			��
	����ֵ
		0�ɹ�		��0ʧ��

 */
int INS_ImportSessionKeyEx(int sockFd, char*keyID, SymmEncryptParam *decKeyParam,
						   char* importKeyType, char *szImportKeyID, 
						   unsigned char* wrappedKey, int wrapedKeyLen );
/* 9.	delete session key ��ʱ��ʵ��

	����˵��
		int sockFd				in		socket ���
		char *szkeyID			in		��ԿID��Ψһ��ʶ��
	
	˵��:
			��
	����ֵ
		0�ɹ�		��0ʧ��



 int INS_DeleteSessionKey(int sockFd, char *szkeyID );
 */
/* 10.	session key encrypt

	����˵��
		int sockFd				in		socket ���
		unsigned char* data		in		������ԭ�ģ������ƣ�
		int iLen				in		������ԭ�ĳ���
		char* szKeyID			in		��ԿID��Ψһ��ʶ��
		int  mode				in		����ģʽ��ģʽ&&��λ
		unsigned char* crypto	out		���ܽ���������ƣ�
		int* iCryptoLen			in/out	���ܽ������
	
	˵��:
			��֧��ECBģʽ�ӽ���
	����ֵ
		0�ɹ�		��0ʧ��

 */


int INS_Encrypt(int sockFd,char* szKeyID, int  mode,
				unsigned char* data, int iLen,
				unsigned char* crypto, int * iCryptoLen );

int INS_EncryptWithKeyID(int sockFd,
						 char* szKeyID, SymmEncryptParam *encParam,
						 unsigned char* data, int iLen,
						 unsigned char* crypto, int * iCryptoLen );

int INS_EncryptWithKey(int sockFd, const unsigned char * key, int len, SymmEncryptParam *encParam,
				 const unsigned char* data, int iLen,	unsigned char* crypto, int * iCryptoLen );
/* 11.	session key decrypt

	����˵��
		int sockFd				in		socket ���
		unsigned char* crypto	in		�������ģ������ƣ�
		int iCryptoLen			in		�������ĳ���
		char* szKeyID			in		��ԿID��Ψһ��ʶ��
		int  mode				in		���ܵĲ�λģʽ(�ο��Ϻ���INS_Encrypt)
		unsigned char* data		out		������ԭ�ģ������ƣ�
		int iLen				in		������ԭ�ĳ���
	
	˵��:
			��֧��ECBģʽ�ӽ���
	����ֵ
		0�ɹ�		��0ʧ��

 */

int INS_Decrypt(int sockFd,char* szKeyID, int  mode, 
				unsigned char* crypto, int iCryptoLen, 
				unsigned char* data, int *iLen );

int INS_DecryptWithKeyID(int sockFd, 
						 char* szKeyID, SymmEncryptParam *decParam,
						 unsigned char* crypto, int iCryptoLen, 
						 unsigned char* data, int *iLen );

int INS_DecryptWithKey(int sockFd, const unsigned char * key, int len, SymmEncryptParam *decParam,
				  const unsigned char* crypto, int iCryptoLen, unsigned char* data, int *iLen );
/* 12.	gen random

	����˵��
		int sockFd				in		socket ���
		unsigned char* data		out		����������ڴ棨�����ƣ�
		int iLen				in		����������ĳ���
	
	˵��:
			��
	����ֵ
		0�ɹ�		��0ʧ��

 */
int INS_GenRandom(int sockFd, unsigned char* data, int iLen );

/* 13.	hash data

	����˵��
		int sockFd				in		socket ���
		char *digestAlg			in		hash�㷨 MD5, SHA1, SHA256, SHA512, SM3......
		unsigned char* pMsg		in		��ժҪ���ݣ������ƣ�
		int pMsgLen				in		��ժҪ���ݳ���
		unsigned char* pDigest	out		ժҪ����������ƣ�
		int *pDigestLen			in/out	ժҪ����������
	
	˵��:
			��
	����ֵ
		0�ɹ�		��0ʧ��

 */

int INS_HashData (int sockFd, char *digestAlg, 
				  unsigned char* pMsg, int pMsgLen, 
				  unsigned char* pDigest,int* pDigestLen);


/* 14.	Detachedǩ����hash��
 
	Dettachǩ��
	int sockFd				in	ǩ�����������Ӿ��
	unsigned char* plain	in	ԭʼ���ݣ�hash)��ַ
	int iPlainLen			in	ԭʼ���ݣ�hash)����
	char* signCertDN		in	ǩ����֤��DN
	char* digestAlg			in	ǩ��ժҪ�㷨  
	unsigned char* crypto	out	ǩ�����ݵ�ַ
	int* iCryptoLen			out	ǩ�����ݳ���
	����ֵ
		0	�ɹ�
		����	ʧ��
˵��:
(1) cryptoʹ�õ��ڴ�ռ��ɵ��ýӿڵ�Ӧ�ó�����������ͷ�;
(2) ǩ�����û�����κ�ת��, ��Ҫת����Base64����������е��ñ��ӿ����ṩ��EncodeBase64�����б���;
(3) ��ǩʱ���͵�ǩ��ֵ�������ʹ�ô˽ӿڷ��صĳ���, ǧ��Ҫ��strlen(crypto)�����ǩ��ֵ���ȣ�

*/
int INS_DetachedSignHash(int sockFd, unsigned char* plain, int iPlainLen, char* signCertDN,	
					 char* digestAlg, unsigned char* crypto, int* iCryptoLen);
						  
						  
/* 15.	Detached��ǩ����hash��
 
	Dettached��ǩ
	int sockFd				in	ǩ�����������Ӿ��
	unsigned char* plain	in	ԭʼ���ݣ�hash)��ַ
	int iPlainLen			in	ԭʼ���ݣ�hash)����
	unsigned char* crypto	in	ǩ�����ݵ�ַ
	int iCryptoLen			in	ǩ�����ݳ���
	int iReturnCert			in	֤��ѡ�� 0:������֤��ʵ��; 1: ����֤�鼰֤��ʵ��; 2: ɾ��֤��; 3: �ϴ�֤�� 
	CERTINFO* result		out	֤����Ϣ�洢��ַ
	����ֵ
		0	�ɹ�
		����	ʧ��
˵��:
(1) resultʹ�õ��ڴ�ռ��ɵ��ýӿڵ�Ӧ�ó�����������ͷ�;
(2) ǩ��ֵ���յĸ�ʽ�Ƕ�����
(3) ����ǩ����ΪBase64�ģ������е��ñ��ӿ����ṩ��DecodeBase64�����н����ٽ�����ǩ;
(4) ��ǩʱ���͵�ǩ��ֵ�������ʹ��ǩ��ֵʵ�ʵĳ���, ǧ��Ҫ��strlen(crypto)������ǩ��ֵ���ȣ�

*/
int INS_DetachedVerifyHash(int sockFd, unsigned char* crypto, int iCryptoLen, char* digestAlg,
					   unsigned char* plain, int iPlainLen, int iReturnCert, CERTINFO *cinfo);

					
							



/*���лƽ�����Ŀ��չ�ӿ�*/


/* 1.	rewrap session key��pubkey encrypt��

	����˵��
		int sockFd				in		socket ���
		char* encCertDN			in		����֤��DN���кţ����Ϊnull��ʹ�÷�����Ĭ��֤�飩
		unsigned char* wrappedKey in	��Կ������֤�鹫Կ���ܺ�ĻỰ��Կ�������ƣ�
		int wrapedKeyLen		in		��Կ���ȣ�byte �ֽڳ��ȣ�
		char* masterKeyLabel	in		����ԿID��������������ĻỰ��Կ
		unsigned char* crypto	out		ת���ܽ���������ƣ�
		int* iCryptoLen			in/out	ת���ܽ������

	
	˵��:
			��
	����ֵ
		0�ɹ�		��0ʧ��

 */

int SGERewrapSessionKey(int sockFd, char* encCertDN, unsigned char* wrappedKey, int wrapedKeyLen, char* masterKeyLabel,unsigned char* crypto, int* iCryptoLen);



/* 2.	session key encrypt

	����˵��
		int sockFd				in		socket ���
		char* masterKeyLabel	in		����ԿID
		char* KeyType			in		��Կ����
		unsigned char* wrappedKey in	��Կֵ������Կ���ܱ�����
		int wrapedKeyLen		in		��Կֵ����
		unsigned char* plain	in		������ԭ�ģ������ƣ�
		int plainLen			in		������ԭ�ĳ���
		unsigned char* crypto	out		���ܽ���������ƣ�
		int* iCryptoLen			in/out	���ܽ������
	
	˵��:
			��֧��ECBģʽ�ӽ��ܣ�KeyType ���� ��SM4����Ŀǰ��Ŀָ��ʹ�ô��㷨�� 
	����ֵ
		0�ɹ�		��0ʧ��

 */

int SGESessionKeyEncrypt(int sockFd, char* masterKeyLabel, char* szKeyType,unsigned char* wrappedKey, int wrapedKeyLen, 
						 unsigned char* plain, int plainLen,  unsigned char* crypto, int* iCryptoLen);


/* 3.	session key decrypt

	����˵��
		int sockFd				in		socket ���
		char* masterKeyLabel	in		����ԿID
		char* KeyType			in		�Ự��Կ����
		unsigned char* wrappedKey in	��Կֵ������Կ���ܱ�����
		int wrapedKeyLen		in		��Կֵ����
		unsigned char* crypto	in		���������ģ������ƣ�
		int iCryptoLen			in		���ĳ���
		unsigned char* plain	out		���ܺ��ԭ�ģ������ƣ�
		int *plainLen			in/out	ԭ�ĳ���
	
	˵��:
			��֧��ECBģʽ�ӽ��ܣ�KeyType ���� ��SM4����Ŀǰ��Ŀָ��ʹ�ô��㷨��
	����ֵ
		0�ɹ�		��0ʧ��

 */

int SGESessionKeyDecrypt(int sockFd, char* masterKeyLabel, char* szKeyType,unsigned char* wrappedKey, int wrapedKeyLen,  
						 unsigned char* crypto, int iCryptoLen, unsigned char* plain, int *plainLen);


/**************************************************************************************/
/******************************����ʶ��֧���ӿ�API**************************************/
/**************************************************************************************/

int makeSpecialWLEnvelope(int sockFd, 
						  int PinBlockNum, DataLV pinBlocks[], char * keyID, SymmEncryptParam *pinDecParam,
						  int NoPaddingNum, DataLV noPaddingDatas[], 
						  int PaddingNum, DataLV PaddingDatas[],
						  SymmEncryptParam *encParam, char* encCertDN,
						  char * cipherText, int cipherMaxSize,
						  DataLV *cryptoEnv, DataLV cryptoPinBlocks[], DataLV cryptoNoPaddingDatas[], DataLV cryptoPaddingDatas[]);

int decryptSpecialWLEnvelope(int sockFd, 							  
							 int PinBlockNum, DataLV cryptoPinBlocks[], char * keyID, SymmEncryptParam *pinEncParam,
							 int NoPaddingNum, DataLV cryptoNoPaddingDatas[], 
							 int PaddingNum, DataLV cryptoPaddingDatas[],
							 DataLV *cryptoEnv, SymmEncryptParam *decParam, char* decCertDN,
							 char * plainText, int plainMaxSize,
							 DataLV pinBlocks[], DataLV noPaddingDatas[], DataLV PaddingDatas[]);


/*ˢ��֧�������ŷ���ܣ�����֧����*/

int FacePayEnvelopeEncryptSimple(int sockFd, char* certDN, SymmEncryptParam *symmAlgParam, 
						   unsigned char* plainText, int plainTextLen,
						   ins_encode_type cryptoTextEncoding,
						   unsigned char* cryptoEnv, int *envLen, 
						   unsigned char* cryptoText,int *cryptoLen);
/*ˢ��֧�������ŷ���ܣ�����֧����*/
int FacePayEnvelopeDecryptSimple(int sockFd, char* certDN, SymmEncryptParam *symmAlgParam, 
							ins_encode_type cryptoTextEncoding,
							unsigned char* cryptoEnv, int envLen, unsigned char* cryptoText, int cryptoLen, 
							unsigned char* plainText, int *plainTextLen);



/*ˢ��֧�� rsa��Կ����pinblock תΪ �Գ���Կ���� pinblock������֧����*/
int FacePayOffLineRawPinBlock2EncPinBlock(int sockFd, char* oldDN, ins_encode_type oldTextEncoding, char* oldCryptoText, int oldCryptoLen, 
										  char* newKeyLable, SymmEncryptParam *symmAlgParam, 
										  ins_encode_type newTextEncoding, unsigned char* newCryptoText, int *newCryptoLen);


/*ˢ��֧�� rsa��Կ����pinblock תΪ �Գ���Կ���� pinblock������ָ��PinBlockλ����*/
int RawEnvelope2EncPinBlockSimple(int sockFd, int is_to_byte8, 
								  char* oldDN, char* oldAcco, ins_encode_type oldTextEncoding, char* oldCryptoText, int oldCryptoLen, 
								  char* newKeyLable, char* newAcco, SymmEncryptParam *symmAlgParam, ins_encode_type newTextEncoding, unsigned char* newCryptoText, int *newCryptoLen);
/**************************************************************************************/
/******************************�����������ӿ�API**************************************/
/**************************************************************************************/

/*
    ����JSON���ĵı�������(������) ("UTF-8"|"GBK")
	˵����
	     1 ��������ñ������ͣ�ʹ��Ĭ�ϱ��� UTF-8��������Ŀ���ʹ�õ���UTF-8���룬������ô˽ӿڡ�
		 2 �˺��������õ���ȫ�ֱ��������̰߳�ȫ����������ֻ��Ҫ����һ�Σ���Ҫ�������ô˽ӿ�����
*/
int CUPCQPSetMessageEncoding(char * encoding);

/*
    ����&ǩ��
	����˵��
		int sockFd				[in]		socket ���
		char* inJsonMessage		[in]		�������ԭ�ģ�JSON��ʽ��
		char* encCertID			[in]		����֤���ʶ
		char* sigCertID			[in]		ǩ��֤���ʶ
		char* outJsonMessage	[out]		���ռ���&ǩ����ı��ĵĻ�����
		int maxLen				[in]		outJsonMessage ����������󳤶ȣ���ֹ�������ڴ�Խ�磩


	˵��:
		��
	����ֵ
		0�ɹ�		��0ʧ��
*/
int CUPCQPEncryptAndSign(int sockFd, char* inJsonMessage, char* encCertID, char* sigCertID, char* outJsonMessage, int maxLen);

/*
    ����&��֤
	����˵��
		int sockFd				[in]		socket ���
		char* inJsonMessage		[in]		�������ԭ�ģ�JSON��ʽ��
		char* encCertID			[in]		����֤���ʶ
		char* sigCertID			[in]		ǩ��֤���ʶ
		char* outJsonMessage	[out]		���ս���&��ǩ�ɹ��ı��ĵĻ�����
		int maxLen				[in]		outJsonMessage ����������󳤶ȣ���ֹ�������ڴ�Խ�磩


	˵��:
		��
	����ֵ
		0�ɹ�		��0ʧ��
*/
int CUPCQPDecryptAndVerify(int sockFd, char* inJsonMessage, char* encCertID, char* sigCertID, char* outJsonMessage, int maxLen);


/*
    ����JSON���ĵı�������(һ����) ("UTF-8"|"GBK")
	˵����
	     1 ��������ñ������ͣ�ʹ��Ĭ�ϱ��� UTF-8��������Ŀ���ʹ�õ���UTF-8���룬������ô˽ӿڡ�
		 2 �˺��������õ���ȫ�ֱ��������̰߳�ȫ����������ֻ��Ҫ����һ�Σ���Ҫ�������ô˽ӿ�����
*/
int CUPBindCardSetMessageEncoding(char * encoding);

/*
    ����&ǩ��2(һ����)
	����˵��
		int sockFd				[in]		socket ���
		char* inJsonMessage		[in]		�������ԭ�ģ�JSON��ʽ��
		char* encCertID			[in]		����֤���ʶ(����keylabel)
		char* sigCertID			[in]		ǩ��֤���ʶ(����keylabel)
		char* outJsonMessage	[out]		���ռ���&ǩ����ı��ĵĻ�����
		int maxLen				[in]		outJsonMessage ����������󳤶ȣ���ֹ�������ڴ�Խ�磩


	˵��:
		��
	����ֵ
		0�ɹ�		��0ʧ��
*/
int CUPBindCardEncryptAndSign(int sockFd, char* inJsonMessage, char* encCertID, char* sigCertID, char* outJsonMessage, int maxLen);

/*
    ����&��֤2(һ����)
	����˵��
		int sockFd				[in]		socket ���
		char* inJsonMessage		[in]		�������ԭ�ģ�JSON��ʽ��
		char* encCertID			[in]		����֤���ʶ(����keylabel)
		char* sigCertID			[in]		ǩ��֤���ʶ(����keylabel)
		char* outJsonMessage	[out]		���ս���&��ǩ�ɹ��ı��ĵĻ�����
		int maxLen				[in]		outJsonMessage ����������󳤶ȣ���ֹ�������ڴ�Խ�磩


	˵��:
		��
	����ֵ
		0�ɹ�		��0ʧ��
*/
int CUPBindCardDecryptAndVerify(int sockFd, char* inJsonMessage, char* encCertID, char* sigCertID, char* outJsonMessage, int maxLen);


/*
    ������ݼ���(һ����)
*/
int CUPBindCardEnc(int sockFd, unsigned char* plain, int iTotlenum, int iPlainlenserial[], 
				char* encCertId, char* Alg, unsigned char* crypto, int iCryptolenserial[], unsigned char* cryptoEnv, int* pCryptoenvlen);

int CUPBindCardDec(int sockFd, unsigned char* crypto, int iTotlenum, int iCryptolenserial[], 
				unsigned char* cryptoEnv, int iCryptoenvlen, char* decCertID, char* Alg, unsigned char* plain, int iPlainlenserial[]);

/**************************************************************************************/
/************���ص�һ����ҵ����ϵͳ������ó�ף�JCE&C�ӿڶԽ���ĿAPI*************************/
/**************************************************************************************/
/*
    �ļ�����
	����˵��
		int sockFd					[in]		socket ���
		char * filename				[in]		�ļ�����
		int type					[in]		��������
		unsigned char * write_data	[in]		д����������(type Ϊ3, 4ʱ�˲���������)
		int write_len				[in]		д�����ݳ���(type Ϊ3, 4ʱ�˲���������)
		unsigned char * read_data	[in]		��ȡ��������(opttype Ϊ2ʱ�˲���������)
		int *read_len				[in/out]	�����������������Ҫ��ȡ�����ݳ��ȣ����ʵ�ʶ�ȡ�����ݳ���(opttype Ϊ2ʱ�˲���������)

	˵��:
		[int type] ��������ȡֵ��1-����|2-��ȡ|3-д��(׷��)|4-д�루���ǣ�|5-ɾ��
		[unsigned char * write_data] ��[int write_len]������ ��������Ϊ 3��4ʱ��Ч
		[unsigned char * read_data] ��[int *read_len]������ ��������Ϊ 2ʱ��Ч

	����ֵ
		0�ɹ�		��0ʧ��
*/

int INS_FileOption(int sockFd, char * filename, int type, unsigned char * write_data, int write_len, unsigned char * read_data, int *read_len);

/*
    ��ȡ�豸��Ϣ
	����˵��
		int sockFd					[in]		socket ���
		char * dev_info				[out]		��ȡ��������
		int max_len					[in]		dev_info ָ����ڴ���󳤶�

	˵��:
		char * dev_info ������������ʵ�ʳ��� �� strlen����

	����ֵ
		0�ɹ�		��0ʧ��
*/
int INS_GetDeviceInfo(int sockFd, char * dev_info, int max_len);

/**************************************************************************************/
/************               �������С��ͬ��ר��API             *************************/
/**************************************************************************************/

/*keyType ȡֵ��Χ*/
#define PBCCN_ZMK  "mk"    /*����Կ*/
#define PBCCN_ZPK  "pk"    /*����PIN������Կ*/
#define PBCCN_ZEK  "ek"    /*���������Կ */


#define  PBCCN_ENCODING_BINARY		(INS_ENCODING_BINARY)
#define  PBCCN_ENCODING_HEXSTRING	(INS_ENCODING_HEXSTRING)
#define  PBCCN_ENCODING_BASE64		(INS_ENCODING_BASE64)

/*
    1 ���ɶԳ���Կ�����ܵ���
*/

int PBCCNCCGenSymmKey(int sockFd,  char* sAlg, char* keyLable, char* keyType,  int isCovered, unsigned char *cryptoText,  int *cryptoLen );

int PBCCNCCGenSymmKeyEx(int sockFd,  char* sAlg, char* keyLable, char* keyType,  int isCovered, int dataEncoding, unsigned char *cryptoText,  int *cryptoLen );


/*
    2 ɾ���Գ���Կ
*/

int PBCCNCCDeleteSymmKey( int sockFd, char* keyLable, char* keyType, int isRmBackup);

/*
    3 ����Գ���Կ����
*/

int PBCCNCCSymmDecAndSetSymmkey( int sockFd,  char* sAlg, char* keyLable, char* keyType, int isCovered,  unsigned char *cryptoText,  int cryptoLen);

int PBCCNCCSymmDecAndSetSymmkeyEx( int sockFd,  char* sAlg, char* keyLable, char* keyType, int isCovered,  int dataEncoding, unsigned char *cryptoText,  int cryptoLen);
/*
    4 �ع��Գ���Կ
*/
int PBCCNCCRollBackSymmkey( int sockFd, char* keyLable, char* keyType);

/*
    5 PINBlockת����(�򻯲�����ֻ֧�� SM4/ECB/NoPaddingģʽ)
*/
int PBCCNCCRewarpPINBlockSimple( int sockFd, char* account, 
								char* decKeylable, unsigned char *oldCryptoText,  int oldCryptoLen, 
								char* encKeylable, unsigned char *newCryptoText,  int *newCryptoLen);

int PBCCNCCRewarpPINBlockSimpleEx( int sockFd, char* account, 
								char* decKeylable, int oldTextEncoding, unsigned char *oldCryptoText,  int oldCryptoLen, 
								char* encKeylable, int newTextEncoding, unsigned char *newCryptoText,  int *newCryptoLen);
/*
    6 PINBlockת����(����������֧�ֶ���ģʽ)
*/

int PBCCNCCRewarpPINBlock( int sockFd, char* account, 
								char* decKeylable, char*decModAndPadding, unsigned char* decIv, int decIvLen, unsigned char *oldCryptoText,  int oldCryptoLen, 
								char* encKeylable, char*encModAndPadding, unsigned char* encIv, int encIvLen, unsigned char *newCryptoText,  int *newCryptoLen);

/*ע�� outputDataEncoding �ı��������ָ��������� newCryptoText�� �������������encIv�ı���
  encIv �ı�����decIv��oldCryptoTextһ����  ��inputDataEncoding��ָ����*/
int PBCCNCCRewarpPINBlockEx( int sockFd, char* account, 
						  char* decKeylable, char*decModAndPadding, int inputDataEncoding, unsigned char* decIv, int decIvLen, unsigned char *oldCryptoText,  int oldCryptoLen, 
						  char* encKeylable, char*encModAndPadding, int outputDataEncoding, unsigned char* encIv, int encIvLen, unsigned char *newCryptoText,  int *newCryptoLen);

/*
    9 ��ͨ���ݼ���(����������֧�ֶ���ģʽ)
*/

int PBCCNCCSymmEncrypt(int sockFd, char* keyLable, char* keyType, char*modAndPadding, unsigned char* encIv, int encIvLen,
					   unsigned char *plainText,  int plainLen, unsigned char *cryptoText,  int *cryptoLen);

int PBCCNCCSymmEncryptEx(int sockFd, char* keyLable, char* keyType, char*modAndPadding, 
						 int inputDataEncoding, unsigned char* encIv, int encIvLen, unsigned char *plainText,  int plainLen, 
						 int outputDataEncoding, unsigned char *cryptoText,  int *cryptoLen);
/*
    10 ��ͨ���ݽ���(����������֧�ֶ���ģʽ)
*/

int PBCCNCCSymmDecrypt(int sockFd, char* keyLable, char* keyType, char*modAndPadding, unsigned char* decIv, int decIvLen,
					   unsigned char *cryptoText,  int cryptoLen, unsigned char *plainText,  int *plainLen);

int PBCCNCCSymmDecryptEx(int sockFd, char* keyLable, char* keyType, char*modAndPadding, 
						 int inputDataEncoding, unsigned char* decIv, int decIvLen, unsigned char *cryptoText,  int cryptoLen, 
						 int outputDataEncoding, unsigned char *plainText,  int *plainLen);


/* v1.5 �ӿ�*/
/*
��pin����תΪ pinblock�����ĵ���

  ע�� outputDataEncoding �ı��������ָ��������� newCryptoText�� �������������encIv�ı���
  encIv �ı�����decIv��oldCryptoTextһ����  ��inputDataEncoding��ָ����*/
int PBCCNCCRewarpPIN2PINBlock( int sockFd, char* account, 
							  char* decKeylable, char*decModAndPadding, int inputDataEncoding, unsigned char* decIv, int decIvLen, unsigned char *oldCryptoText,  int oldCryptoLen, 
							  char* encKeylable, char*encModAndPadding, int outputDataEncoding, unsigned char* encIv, int encIvLen, unsigned char *newCryptoText,  int *newCryptoLen);
/*
��pinblock����תΪ pin�����ĵ���

  ע�� outputDataEncoding �ı��������ָ��������� newCryptoText�� �������������encIv�ı���
  encIv �ı�����decIv��oldCryptoTextһ����  ��inputDataEncoding��ָ����*/
int PBCCNCCRewarpPINBlock2PIN( int sockFd, char* account, 
							char* decKeylable, char*decModAndPadding, int inputDataEncoding, unsigned char* decIv, int decIvLen, unsigned char *oldCryptoText,  int oldCryptoLen, 
							char* encKeylable, char*encModAndPadding, int outputDataEncoding, unsigned char* encIv, int encIvLen, unsigned char *newCryptoText,  int *newCryptoLen);
/*
���������Կ������֤��Կ����ȷ��
*/
int PBCCNCCSymmDecAndSetSymmkeyWithCheck( int sockFd,  char* sAlg, char* keyLable, char* keyType, int isCovered, int isRealTimeSync, 
										 int dataEncoding, unsigned char *cryptoText,  int cryptoLen, 
										 unsigned char *checkPlainText,  int checkPlainLen, char* checkModAndPadding, 
										 int CheckEncoding, unsigned char* checkIv, int checkIvlen, unsigned char *checkCryptoText, int checkCryptoLen);

/**************************************************************************************/
/************               ����������֧������ӿ�API           *************************/
/**************************************************************************************/
/*���������ŷ�ת��PinBlock��ԭʼ��ʽ��
��������������ŷ���������ݶ�û��base64����*/
int WLEnvelope2EncPinBlock(int sockFd, int blockNum, int is_to_byte8,
						   char* oldDN, char* oldAcco, unsigned char *oldCryptoEnv, int oldEnvLen,
						   unsigned char* oldCryptoText, int oldCryptoLens[],
						   char* newKeyLable, char* newAcco, char* modAndPadding, unsigned char* iv, int ivlen,
						   unsigned char* newCryptoText, int newCryptoLens[], int maxNewCryptoText);

/*���������ŷ�ת�������ŷ⣨ԭʼ��ʽ��
��������������ŷ���������ݶ���ԭʼ��ʽ���ǿɼ��ַ�����*/
int WLEnvelope2WLEnvelope(int sockFd, int blockNum, char* encAlg,
						  char* oldDN, char* oldAcco, unsigned char *oldCryptoEnv, int oldEnvLen,
						  unsigned char* oldCryptoText, int oldCryptoLens[],
						  char* newDN, char* newAcco, unsigned char* newCryptoEnv, int *newEnvLen,
						  unsigned char* newCryptoText, int newCryptoLens[], int maxNewCryptoText);

/*PinBlockת�������ŷ⣨ԭʼ��ʽ��
��������������ŷ���������ݶ���ԭʼ��ʽ���ǿɼ��ַ�����*/
int EncPinBlock2WLEnvelope(int sockFd, int blockNum, int is_to_byte8,
						   char* oldKeyLable, char* oldAcco, char* modAndPadding, unsigned char* iv, int ivlen,
						   unsigned char* oldCryptoText, int oldCryptoLens[],
						   char* newDN, char* newAcco, char* encAlg, unsigned char *newCryptoEnv, int *newEnvLen,
						   unsigned char* newCryptoText, int newCryptoLens[], int maxNewCryptoText);

/*���ܲ����ù�����Կ���������ϣ�ԭʼ��ʽ��
��������ĺ�IV ��ԭʼ��ʽ���ǿɼ��ַ���*/

int symmDecAndSetSymmkey(int sockFd, 
						 char* decKeyLabel, char* modAndPadding, unsigned char* iv, int ivlen,
						 unsigned char* cryptoText, int cryptoTextLen,
						 char *newKeyLabel, char* newKeyAlg);

int asymmDecAndSetSymmkey(int sockFd, char* decCerDN,
						 unsigned char* cryptoText, int cryptoTextLen,
						 char *newKeyLabel, char* newKeyAlg);


/*����ֱ�Ӳ����ӿ�
ʹ��ע��
1 �ӿڷ��̰߳�ȫ����Ҫ���߳�ʹ��ͬһ��hMsg
2 */
typedef void*  MSG_HANDLE;

typedef int (*fn_raw_message_init_callback)(char * processor, MSG_HANDLE * phMsg);
typedef int (*fn_raw_message_free_callback)(MSG_HANDLE hMsg);
typedef int (*fn_raw_message_set_str_callback)(MSG_HANDLE hMsg, unsigned char tag, char* message);
typedef int (*fn_raw_message_set_data_callback)(MSG_HANDLE hMsg, unsigned char tag, unsigned char* message, unsigned int len);
typedef int (*fn_raw_message_send_recv_callback)(MSG_HANDLE hMsg, int sockFd, int timeout);
typedef int (*fn_raw_message_get_data_callback)(MSG_HANDLE hMsg, unsigned char tag, const unsigned char ** dataRef, unsigned int *len);
typedef int (*fn_raw_message_copy_data_callback)(MSG_HANDLE hMsg, unsigned char tag, unsigned char *copydata, unsigned int *copylen);
typedef struct raw_message_callback_st
{
	unsigned char ver;/*if init already,set 0x10; v1.0*/
	fn_raw_message_init_callback msg_init;
	fn_raw_message_free_callback msg_free;
	fn_raw_message_set_str_callback msg_set_str;
	fn_raw_message_set_data_callback msg_set_data;
	fn_raw_message_send_recv_callback msg_send_recv;
	fn_raw_message_get_data_callback msg_get_data;
	fn_raw_message_copy_data_callback msg_copy_data;	
}RAW_MESSAGE_CALLBACK_ST;
int GetNetSignRawMessageCallback(RAW_MESSAGE_CALLBACK_ST **callback_ref);





/*CUP��������ŷ�ӽ���*/
typedef void*  CUP_ENV_HANDLE;

typedef enum
{
	SEN_TYPE_NORMAL = 0,/*��ͨ��������*/
	SEN_TYPE_PIN_BLOCK,/*��ͨ PinBlock ����,����PinBlockת��*/
	SEN_TYPE_PIN_2_PIN_BLOCK,/*Pin �ϳ� PinBlock���ɺϳ�PinBlock*/
	SEN_TYPE_ROUTE_INDEX,/*·������ ��pin*/
	SEN_TYPE_PIN_BLOCK_CQP,/*��������PinBlock*/
	SEN_TYPE_PIN_2_PIN_BLOCK_CQP,/*��������Pin ת PinBlock*/
	SEN_TYPE_ROUTE_INDEX_WITH_PIN_BLOCK,/*·������ ��PinBlock*/
	SEN_TYPE_PIN_BLOCK_2_PIN,/*PinBlock ��ȡ Pin�� �ɴ�PinBlock��ȡPin*/
}ENUM_SEN_TYPE;

int CUPMultiEnvelopeInit( char* certId, unsigned int senGroupNum, CUP_ENV_HANDLE * hEnv);

int CUPMultiEnvelopeFree(CUP_ENV_HANDLE hEnv);

int CUPMultiEnvelopeSendMsg(int sockFd, CUP_ENV_HANDLE hEnv, unsigned int is_encrypt);


int CUPMultiEnvelopSetEnvelope(CUP_ENV_HANDLE hEnv, ins_encode_type encodeType, unsigned char*data, unsigned int len);

int CUPMultiEnvelopGetEnvelope(CUP_ENV_HANDLE hEnv, ins_encode_type encodeType, unsigned char*data, unsigned int *len);

int CUPSenInfoSetType(CUP_ENV_HANDLE hEnv, unsigned int senIndex, ENUM_SEN_TYPE senType);


int CUPSenInfoAddData(CUP_ENV_HANDLE hEnv, unsigned int senIndex, unsigned int* dataIndex, 
					  ins_encode_type encodeType, unsigned char*data, unsigned int len);

int CUPSenInfoGetResult(CUP_ENV_HANDLE hEnv, unsigned int senIndex, unsigned int retIndex, 
					  ins_encode_type encodeType, unsigned char*data, unsigned int *len);

int CUPSenInfoSetAlgParam(CUP_ENV_HANDLE hEnv, unsigned int senIndex, 
						  char* alg, ins_encode_type encodeType, unsigned char*iv, unsigned int ivlen);

int CUPSenInfoSetPinParam(CUP_ENV_HANDLE hEnv, unsigned int senIndex, 
						  char* label, char* modePadding, ins_encode_type encodeType, unsigned char*piniv, unsigned int ivlen);

int CUPSenInfoSetCardNums(CUP_ENV_HANDLE hEnv, unsigned int senIndex, 
						  char* cardNum, char* newCardNum, unsigned int pinBytes/*8 or 16 bytes*/);/*�����û�����*/

/*������չ��Ϣ*/
int CUPSenInfoSetExtend(CUP_ENV_HANDLE hEnv, unsigned int senIndex, 
						char* extEnd);

/*���÷������ĵĸ�ʽ�� 0 DER���룬 1  RAW���롣Ĭ�� 0*/
int CUPSenInfoSetRetType(CUP_ENV_HANDLE hEnv, unsigned int senIndex, 
						unsigned char retType);


/************************************************************************/
/* ����������ҵ�����˲�ӿ�                                                     */
/************************************************************************/

/* 1.	����P10������
 
    ������Կ�ԣ�������P10������

	int sockFd				in	ǩ�����������Ӿ��
	char* certDN			in	֤��DN
	char* keyID				in	��Կ��id
	char* keyType			in	��Կ����(RSA1024|RSA2048|SM2)
	int isCover				in	���keyID�Ѿ������ڷ��������Ƿ񸲸�
	unsigned char* p10Data	out	������P10������
	int iCryptoLen			in/out	����p10Data����ĳ��ȣ�����ʵ�ʵ�p10���������ݵĳ���
	����ֵ
		0	�ɹ�
		����	ʧ��
˵��:
(1) ���isCover=0���������Ѵ�����Կ��һ����������ȷ������Կ������ֱ�ӱ�����
(2) �����p10������Ϊbase64�����ʽ

*/

int INS_KPLGenP10Req(int sockFd, char* certDN, char* keyID, char* keyType, int isCover, unsigned char* p10Data, unsigned int *p10Len);

/* 2.	����֤��(��֤)���ǶԳ���Կ������
 
	int sockFd				in	ǩ�����������Ӿ��
	char* keyID				in	��Կ��id�������루INS_KPLGenP10Req��ʱ����ͬ��id
	unsigned char* certData	in	֤����������(base64�����p7b��cer֤��)
	unsigned int certLen	in	֤�����ݳ���
	����ֵ
		0	�ɹ�
		����	ʧ��
˵��:
(1) ����֤������ֻ֧��base64����

*/
int INS_KPLImportCert(int sockFd, char* keyID, unsigned char* certData, unsigned int certLen);



/* 3.	��ȡCRL������֤������
 
    ָ��CA���������������ȡ��CRL������֤�������

	int sockFd				in	ǩ�����������Ӿ��
	char* rootCertDN		in	���������ƻ���CA������
	char trustField[256]	out	���CRL������������
	unsigned int *crlCount	out	����ʵ������֤�����
	����ֵ
		0	�ɹ�
		����	ʧ��
˵��:��

*/

int INS_KPLCountCRL(int sockFd, char* rootCertDN,  char trustField[256], unsigned int *crlCount);

/* 4.	��ȡ֤���б���֤����Ϣ
 
     �����б��ǶԳ���Կ���б�����н��ڻ����б��е�֤����Ϣ(bankid, ���кţ�����DN)

	int sockFd				in	ǩ�����������Ӿ��
	int flag				in	=0�������ǶԳ���Կ���������е�֤�飬 = 1���������н��ڻ����б�������֤��
	KPLCertInfo certInfos[]	out	���֤����Ϣ�Ľṹ�б�
	unsigned int *len		in/out	KPLCertInfo�����Ԫ�ظ����� �������Ԫ������������ʵ�ʵ�֤�����
	����ֵ
		0	�ɹ�
		����	ʧ��
˵��:
(1) ��flag=1ʱ�� ������Ϣ��KPLCertInfo::bankid��Ϣ

*/
typedef struct KPL_CERT_INFO
{
	char bankid[64];					/*bankid���� keyid*/
	char serialNumber[40];				/* ֤�����к�*/
	char subject[256];					/* ֤������*/
}KPLCertInfo;

int INS_KPLGetCertList(int sockFd, int flag, KPLCertInfo certInfos[], unsigned int *len);

/* 5.	��ȡ�ǶԳ���Կ�б�����Կ�Ժ�֤������

	int sockFd					in	ǩ�����������Ӿ��
	unsigned int *keypairCount	out	��Կ������
	unsigned int *certCount		out	֤������
	����ֵ
		0	�ɹ�
		����	ʧ��
˵��:
(1) keypairCount �� certCount����ͬʱΪnull
*/

int INS_KPLCountKeyPairsAndCerts(int sockFd, unsigned int *keypairCount, unsigned int *certCount);

/* 6.	����������ҵ�����˲���ǩ��

	int sockFd				in	ǩ�����������Ӿ��
	unsigned char* data		in	��ǩ�����ݣ������ƣ�
	int iLen				in	��ǩ�����ݳ���
	char* keyID				in	ǩ����Կ�Ե�id���ǿգ�
	char *digestAlg			in	ǩ����hash�㷨���ǿգ�
	int flag				in	������������������Ϊ0
	ins_encode_type dataEncType	in	ǩ������ĸ�ʽ (������|16�����ַ���|base64...)
	unsigned char* crypto	out	ǩ���������ʽ��dataEncTypeԼ����
	int iCryptoLen			in/out	ǩ���������
	����ֵ
		0	�ɹ�
		����	ʧ��
˵��:��

*/

int INS_KPLRawSignData(int sockFd, unsigned char* data, int iLen, 
					char* keyID, char *digestAlg, int flag, 
					ins_encode_type dataEncType, unsigned char* crypto, int* iCryptoLen);

/* 7.	����������ҵ�����˲�����ǩ

	int sockFd				in	ǩ�����������Ӿ��
	unsigned char* data		in	��ǩ�����ݣ������ƣ�
	int iLen				in	��ǩ�����ݳ���
	char* keyID				in	ǩ����Կ�Ե�id���ǿգ�
	char *digestAlg			in	ǩ����hash�㷨���ǿգ�
	int flag				in	=0����֤CRL�б�������ڣ��� =1 ����(����)CRL�б����֤
	ins_encode_type dataEncType	in	ǩ������ĸ�ʽ (������|16�����ַ���|base64...)
	unsigned char* crypto	in	ǩ���������ʽ��dataEncTypeԼ����
	int iCryptoLen			in	ǩ���������
	����ֵ
		0	�ɹ�
		����	ʧ��
˵��:��

*/

int INS_KPLRawVerifyData(int sockFd, unsigned char* data, int iLen, 
					  char* keyID, char *digestAlg, int flag, 
					  ins_encode_type dataEncType, unsigned char* crypto, int iCryptoLen);
/* 8.	�鿴�������ж�����Դ����ͬ��״̬
 
	�������ķ���������ȡ����ģ�֤�飬�Գ���Կ���ǶԳ���Կ��ͬ��״̬
	int sockFd				in	ǩ�����������Ӿ��
	int type				in	��Դ���� �� 0 ���л����б��е�֤�飬 1 �Գ���Կ��id�� 2 �ǶԳ���Կ��id
	char* resID				in	��ԴID
	char* statusDesc		out	������Դͬ��״̬��Ϣ
	unsigned int *statusLen	in/out	����statusDesc����������󳤶ȣ�����ʵ�ʷ��ڵ���Ϣ����
	����ֵ
		0	�ɹ�
		����	ʧ��
˵��:
(1) ����֤�飬��ԴIDΪ�����š�
(2) ���ڷǶԳ���Գ���Կ�� ��ԴidΪ��Կ��ID��label��
(3) ������Դͬ����ϢΪN����Ϣ(�ɼ��ַ���)�ļ��ϣ�ÿ����Ϣ�� 0x00������ ���е�NΪʵ���ϵ�ͬ��������������
(4) statusLenΪ in/out���Ͳ���������Ϊ statusDescʵ�ʳ��ȣ�Ϊ�˷�ֹcopy�ڴ�Խ�硣�����ⲿ������ʽ��ֵ
(5) INS_KPLCheckPbcCertsSynStatus���������Ǻ���ԭ�ͣ������Ǻ궨�� Ϊ�˴���ɶ��ԡ����Ժ��Դ���

*/
int INS_KPLCheckResourceSynStatus(int sockFd, int type, char* resID, char* statusDesc, unsigned int *statusLen);

#define INS_KPLCheckPbcCertsSynStatus(sockFd, bankCode, StatusList, countList) INS_KPLCheckResourceSynStatus(sockFd, 0, bankCode, StatusList, countList)
#define INS_KPLCheckSymmKeySynStatus(sockFd, symmkeyid, StatusList, countList) INS_KPLCheckResourceSynStatus(sockFd, 1, symmkeyid, StatusList, countList)
#define INS_KPLCheckAsymmSynStatus(sockFd, asymmkeyid, StatusList, countList) INS_KPLCheckResourceSynStatus(sockFd, 2, asymmkeyid, StatusList, countList)

/* 9.	ɾ����Կ��
 
	������Կ�Ե�idɾ����Կ��
	int sockFd				in	ǩ�����������Ӿ��
	char* keyID				in	��Կ�Ե�id
	����ֵ
		0	�ɹ�
		����	ʧ��
˵��:��

*/
int INS_KPLDeleteKeyPair(int sockFd, char* keyID);

#ifdef __cplusplus
}
#endif
#endif /*#ifndef _RH_VERIFY_API_H_*/

