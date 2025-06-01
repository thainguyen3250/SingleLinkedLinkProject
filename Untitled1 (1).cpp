#include "stdio.h"
#include "stdlib.h"
#include "string.h"
//---------------------------hoat dong-----------------------------
typedef struct time
{
	int nam;
	int thang;
	int ngay;
	int gio;
}time;
typedef struct hoat_dong
{
	char tenhd[20];
	time batdau;
	time ketthuc;
	char tentainguyen[50];
}hoat_dong;
typedef struct hoatdong
{
	hoat_dong data;
	hoatdong *pNext;
}hoatdong;
struct list_hd
{
	hoatdong *hd_head;
	hoatdong *hd_tail;
};
void __init_hd__(list_hd &hd)
{
	hd.hd_head = hd.hd_tail=NULL;
}
hoatdong* create_hoatdong(hoat_dong hd)
{
	hoatdong *ptr = new hoatdong;
	ptr->data = hd;
	ptr->pNext = NULL;
	return ptr;
}
void append_hoatdong(list_hd &lhd, hoat_dong hd)
{
	hoatdong *ptr = create_hoatdong(hd);
	if(lhd.hd_head == NULL)
	{
		lhd.hd_head = lhd.hd_tail = ptr;
		return;
	}
	lhd.hd_tail->pNext = ptr;
	lhd.hd_tail = ptr;
	return;
}
void themdau_hoatdong(list_hd &lhd, hoat_dong hd)
{
	hoatdong *ptr = create_hoatdong(hd);
	if(lhd.hd_head == NULL)
	{
		lhd.hd_head = lhd.hd_tail  =ptr;
		return;
	}
	ptr->pNext = lhd.hd_head;
	lhd.hd_head = ptr;
	return;
}
int sosanh(time batdau, time ketthuc);
int check_thoigian(time batdau1, time ketthuc1, time batdau2, time ketthuc2);
int kiem_tra_ngay(int month, int year, int day);
//---------------------------tainguyen------------------
typedef struct tainguyen
{
	char tentn[20];
	list_hd data;	
	tainguyen *pNext;
}tainguyen;
struct list_tn
{
	tainguyen *tn_head;
	tainguyen *tn_tail;
};
void __init_tn__(list_tn &tn)
{
	tn.tn_head = tn.tn_tail = NULL;
}
tainguyen* create_tainguyen(char a[])
{
	tainguyen *ptr = new tainguyen;
	strcpy(ptr->tentn,a);
	__init_hd__(ptr->data);
	ptr->pNext = NULL;
	return ptr;
}
void append_tainguyen(list_tn &ltn, char a[])
{
	tainguyen *ptr = create_tainguyen(a);
	if(ltn.tn_head == NULL)
	{
		ltn.tn_head = ltn.tn_tail = ptr;
		return;
	}
	ltn.tn_tail->pNext = ptr;
	ltn.tn_tail = ptr;	
}
//void xuat_tai_nguyen(list_tn ltn)
//{
//	tainguyen *ptr = ltn.tn_head;
//	int i=0;
//	while (ptr)
//	{
//		printf("\n-----------------TAI NGUYEN THU %d-----------",i+1);
//		printf("\nTen tai nguyen: %s",ptr->tentn);
//		i+=1;
//		ptr=ptr->pNext;
//	}
//}
tainguyen* find_tainguyen_addrs(list_tn ltn, char name[])
{
	 tainguyen *ptr = ltn.tn_head;
	 while (ptr)
	 {
	 	if(strcmp(name,ptr->tentn) == 0)
	 	return ptr;
	 	ptr=ptr->pNext;
	 }
	 return NULL;
}
//--------------------------------------------------------------------------
typedef struct dshd
{
	hoat_dong data;
	dshd *pNext;	
}dshd;
struct dshd_list
{
	dshd *pHead;
	dshd *pTail;
};
void __init__dshd(dshd_list &l)
{
	l.pHead = l.pTail=NULL;
}
dshd* create_dshoatdong(hoat_dong hd)
{
	dshd* ptr = new dshd;
	ptr->data = hd;
	ptr->pNext = NULL;
	return ptr;
}
void append_dshd(dshd_list &l, hoat_dong hd)
{
	dshd* ptr = create_dshoatdong(hd);
	if(l.pHead == NULL)
	{
		l.pHead = l.pTail = ptr;
		return;
	}
	l.pTail->pNext = ptr;
	l.pTail=ptr;
}

//---------------------------------------hoat dong trong tai nguyen--------------------
void nhap_hoat_dong_vao_tai_nguyen(list_tn &tn,dshd_list &l)
{
	int i=1;
	hoat_dong hd;
	do
	{
		printf("\n--------------------------HOAT DONG %d-----------------\n",i);
		printf("\n***Nhap ten hoat dong (Neu hoat dong rong thi dung lai): ");
		fflush(stdin);
		gets(hd.tenhd);
		if(strlen(hd.tenhd)==0)
		break;
		printf("\nA. Nhap thong tin thoi gian bat dau ");	
		printf("\n1. Nhap nam: ");
		scanf("%d",&hd.batdau.nam);
		while(hd.batdau.nam<1900)
		{
			printf("\nNam khong hop le !!");
			printf("\nNhap lai nam: ");
			scanf("%d",&hd.batdau.nam);
		}
		printf("\n2. Nhap thang: ");
		scanf("%d",&hd.batdau.thang);
		while(hd.batdau.thang<0||hd.batdau.thang>12)
		{
			printf("\nThang khong hop le !!");
			printf("\nNhap lai thang: ");
			scanf("%d",&hd.batdau.thang);
		}
		printf("\n3. Nhap ngay: ");
		scanf("%d",&hd.batdau.ngay);
		while(kiem_tra_ngay(hd.batdau.thang,hd.batdau.nam,hd.batdau.ngay))
		{
			printf("\nNhap lai ngay: ");
			scanf("%d",&hd.batdau.ngay);
		}
		printf("\n4. Nhap gio: ");
		scanf("%d",&hd.batdau.gio);
		while(hd.batdau.gio<0||hd.batdau.gio>24)
		{
			printf("\nGio khong hop le !!");
			printf("\nNhap lai gio: ");
			scanf("%d",&hd.batdau.gio);
		}
		
		printf("\nB. Nhap thong tin thoi gian ket thuc");
		printf("\n1. Nhap nam: ");
		scanf("%d", &hd.ketthuc.nam);
		while(hd.ketthuc.nam<1900)
		{
			printf("\nNam khong hop le !!");
			printf("\nNhap lai nam: ");
			scanf("%d",&hd.ketthuc.nam);
		}
		printf("\n2. Nhap thang: ");
		scanf("%d",&hd.ketthuc.thang);
		while(hd.ketthuc.thang<0||hd.ketthuc.thang>12)
		{
			printf("\nThang khong hop le !!");
			printf("\nNhap lai thang: ");
			scanf("%d",&hd.ketthuc.thang);
		}
		printf("\n3. Nhap ngay: ");
		scanf("%d",&hd.ketthuc.ngay);
		while(kiem_tra_ngay(hd.ketthuc.thang,hd.ketthuc.nam,hd.ketthuc.ngay))
		{
			printf("\nNhap lai ngay: ");
			scanf("%d",&hd.ketthuc.ngay);
		}
		printf("\n4. Nhap gio: ");
		scanf("%d",&hd.ketthuc.gio);
		while(hd.ketthuc.gio<0||hd.ketthuc.gio>24)
		{
			printf("\nGio khong hop le !!");
			printf("\nNhap lai gio: ");
			scanf("%d",&hd.ketthuc.gio);
		}
		
		printf("\nC. Nhap ten tai nguyen: ");
		fflush(stdin);
		gets(hd.tentainguyen);		
		if(find_tainguyen_addrs(tn,hd.tentainguyen)==NULL)
		append_tainguyen(tn,hd.tentainguyen);
		tainguyen *ptr= find_tainguyen_addrs(tn,hd.tentainguyen);
		if(sosanh(hd.batdau,hd.ketthuc))
		{
			if(ptr->data.hd_head==NULL)
			{
				append_hoatdong(ptr->data,hd);
				append_dshd(l,hd);
			}
			else
			{
				if(check_thoigian(ptr->data.hd_tail->data.batdau,ptr->data.hd_tail->data.ketthuc,hd.batdau,hd.ketthuc)==2)
				{
					append_hoatdong(ptr->data,hd);
					append_dshd(l,hd);
				}
				else
				{
					if(check_thoigian(ptr->data.hd_head->data.batdau,ptr->data.hd_head->data.ketthuc,hd.batdau,hd.ketthuc)==1)
					{
						themdau_hoatdong(ptr->data,hd);
						append_dshd(l,hd);
					}
					else
					printf("\nHoat dong bi trung lap thoi gian !!");
				}
			}			
		}				
		else
		printf("\nThoi gian dien ra va ket thuc khong hop le !!");
		i+=1;
	}while(1);

}
void xuat_cac_hoat_dong_cung_cac_tai_nguyen(list_tn ltn)
{
	tainguyen *ptr=ltn.tn_head;
	int i=0;
	while (ptr)
	{
		printf("\n-----------------TAI NGUYEN THU %d-----------",i+1);
		printf("\n**. Ten tai nguyen: %s",ptr->tentn);
		i+=1;
		printf("\n**. Cac hoat dong trong tai nguyen ");
		hoatdong *ptr1=ptr->data.hd_head;
		int k=0;
		while(ptr1)
		{
			printf("\n----Hoat dong %d----",k+1);
			printf("\nTen hoat dong: %s",ptr1->data.tenhd);
			printf("\nThoi gian bat dau: %d/%d/%d : %dh",ptr1->data.batdau.ngay,ptr1->data.batdau.thang,ptr1->data.batdau.nam,ptr1->data.batdau.gio);
			printf("\nThoi gian ket thuc: %d/%d/%d : %dh",ptr1->data.ketthuc.ngay,ptr1->data.ketthuc.thang,ptr1->data.ketthuc.nam,ptr1->data.ketthuc.gio);
			k+=1;
			ptr1=ptr1->pNext;	
		}
		ptr=ptr->pNext;
	}
}
int sosanh(time batdau,time ketthuc)
{
	if(batdau.nam<ketthuc.nam)
	return 1;
	else
	{
		if(batdau.nam>ketthuc.nam)
		return 0;
		else
		{
			if(batdau.thang<ketthuc.thang)
			return 1;
			else
			{
				if(batdau.thang>ketthuc.thang)
				return 0;
				else
				{
					if(batdau.ngay<ketthuc.ngay)
					return 1;
					else
					{
						if(batdau.ngay>ketthuc.ngay)
					    return 0;
					    else
					    {
					    	if(batdau.gio<ketthuc.gio)
					    	return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}
int check_thoigian(time batdau1,time ketthuc1,time batdau2,time ketthuc2)
{
	if(sosanh(ketthuc1,batdau2))
	{
		return 2;
	}
	else
	{
		if(sosanh(ketthuc2,batdau1))
		{
			return 1;
		}
	}
	return 0;
}
int kiem_tra_ngay(int month,int year,int day)
{
	if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
	{
		if(day<0 || day>31)
		{
			printf("Ngay khong hop le !!");
			return 1;
		}
	}
	if(month==4||month==6||month==9||month==11)
	{
		if(day<0 || day>30)
		{
			printf("Ngay khong hop le !!");
			return 1;
		}
	}
	if(month==2)
	{
		if ((year % 400 == 0)||(year % 4 == 0 && year % 100 != 0))
		{
			if(day<0 || day>29)
			{
			printf("Ngay khong hop le !!");
			return 1;
			}
		}
		else
		{
			if(day<0 || day>28)
			{
			printf("Ngay khong hop le !!");
			return 1;
			}
		} 			 
	}
	return 0;
}
void search(list_tn ltn,char tentainguyen[])
{
	tainguyen *ptr=find_tainguyen_addrs(ltn,tentainguyen);
	if (ptr==NULL)
	{
		printf("\nKhong ton tai tai nguyen !!");
		return;
	}
	int k=0;
	printf("\n------Thong tin tai nguyen-----");
	printf("\n1.ten tai nguyen:%s",ptr->tentn);
	hoatdong *ptr1=ptr->data.hd_head;
	while(ptr1)
		{
			printf("\n----Hoat dong %d----:",k+1);
			printf("\nTen hoat dong:%s",ptr1->data.tenhd);
			printf("\nThoi gian bat dau: %d/%d/%d : %dh",ptr1->data.batdau.nam,ptr1->data.batdau.thang,ptr1->data.batdau.ngay,ptr1->data.batdau.gio);
			printf("\nThoi gian ket thuc: %d/%d/%d : %dh",ptr1->data.ketthuc.nam,ptr1->data.ketthuc.thang,ptr1->data.ketthuc.ngay,ptr1->data.ketthuc.gio);
			k+=1;
			ptr1=ptr1->pNext;	
		}
}
void xuat_hoat_dong(hoat_dong hd)
{
	printf("\n%-15s|%-15s|%15d/%d/%d%:%dh|%15d/%d/%d:%dh",hd.tenhd,hd.tentainguyen,hd.batdau.ngay,hd.batdau.thang,hd.batdau.nam,hd.batdau.gio,hd.ketthuc.ngay,hd.ketthuc.thang,hd.ketthuc.nam,hd.ketthuc.gio);
}
void xuat_hd(dshd_list ds)
{
	printf("\n%-15s|%-15s|%25s|%25s","Ten hoat dong","Ten tai nguyen","Bat dau","Ket thuc");
	dshd *ptr=ds.pHead;
	while(ptr)
	{
		xuat_hoat_dong(ptr->data);
		ptr=ptr->pNext;
	}
}
void khoitao_hoatdong_tu_danhsach(list_tn &tn,dshd_list l)
{
	dshd *ptr=l.pHead;
	while(ptr)
	{
		if(find_tainguyen_addrs(tn,ptr->data.tentainguyen)==NULL)
		append_tainguyen(tn,ptr->data.tentainguyen);
		tainguyen *ptr1= find_tainguyen_addrs(tn,ptr->data.tentainguyen);
		if(ptr1->data.hd_head==NULL)
			{
				append_hoatdong(ptr1->data,ptr->data);
			}
			else
			{
				if(check_thoigian(ptr1->data.hd_tail->data.batdau,ptr1->data.hd_tail->data.ketthuc,ptr->data.batdau,ptr->data.ketthuc)==2)
				{
					append_hoatdong(ptr1->data,ptr->data);
				}
				else
				{
					if(check_thoigian(ptr1->data.hd_head->data.batdau,ptr1->data.hd_head->data.ketthuc,ptr->data.batdau,ptr->data.ketthuc)==1)
					{
						themdau_hoatdong(ptr1->data,ptr->data);
					}
				}
			}			
		ptr=ptr->pNext;
	}
}
void luufile(dshd_list ds)
{
	FILE *f=fopen("project1.text","wb");
	if(f==NULL)
	{
		printf("\nLoi tao file!");
		return;
	}
	dshd *ptr=ds.pHead;
	while(ptr)
	{
		fwrite(&ptr->data,sizeof(hoat_dong),1,f);
		ptr=ptr->pNext;
	}
	fclose(f);
	printf("\nDa luu file thanh cong!");	
}
void xuat_file(dshd_list &l,list_tn &tn)
{
	FILE *f=fopen("project1.text","rb");
	if(f==NULL)
	{
		printf("\nFile khong ton tai!");
		return;
	}
	hoat_dong hd;
	while(fread(&hd,sizeof(hoat_dong),1,f))
	{
		append_dshd(l,hd);
	}
	fclose(f);
	khoitao_hoatdong_tu_danhsach(tn,l);
	printf("a xuat file thanh cong!");	
}
void xoa_hoat_dong_trong_tai_nguyen(list_tn &l,time start,time end,char tentn[],char tenhoatdong[])
{
	tainguyen* ptr=l.tn_head;
	while(ptr)
	{
		if(strcmp(ptr->tentn,tentn)==0)
		{
			hoatdong* curr=ptr->data.hd_head;
			hoatdong* prev=NULL;
			while(curr)
			{
				int flag=0;
				if(strcmp(curr->data.tenhd,tenhoatdong)==0)
				{
					if(curr->data.batdau.ngay==start.ngay&&curr->data.batdau.thang==start.thang&&curr->data.batdau.nam==start.nam)
					{
						if(curr->data.ketthuc.ngay==end.ngay&&curr->data.ketthuc.thang==end.thang&&curr->data.ketthuc.nam==end.nam)
						{
							flag=1;
						}
					}
				}
				if(flag)
				{
					if(prev==NULL)
					{
						ptr->data.hd_head=curr->pNext;
					}
					else
					{
						prev->pNext=curr->pNext;
					}
					if(curr==ptr->data.hd_tail)
					{
						ptr->data.hd_tail=prev;
					}
					hoatdong* temp=curr;
					curr=curr->pNext;
					delete temp;
				}
				else
				{
					prev=curr;
					curr=curr->pNext;
				}
			}
			
		}
		ptr=ptr->pNext;
	}
}
//xoa hoat dong dua tren thoi gian ve ten tai nguyen
void xoa_hoat_dong(dshd_list &l,list_tn &tn,time start,time end,char tentn[])
{
	//dshd_list &l danh sach cac hoat dong,
	//list_tn &tn danh sach cac tai nguyen da duoc khoi tao
	dshd* ptr= l.pHead;
	dshd* previous=NULL;
	while (ptr)
	{
		int flag=0;
		if(strcmp(ptr->data.tentainguyen,tentn)==0)
		{
			if(ptr->data.batdau.ngay==start.ngay&&ptr->data.batdau.thang==start.thang&&ptr->data.batdau.nam==start.nam)
			{
				if(ptr->data.ketthuc.ngay==end.ngay&&ptr->data.ketthuc.thang==end.thang&&ptr->data.ketthuc.nam==end.nam)
				{
					flag=1;
					xoa_hoat_dong_trong_tai_nguyen(tn,start,end,tentn,ptr->data.tenhd);
				}
			}
		}
		if(flag)
		{
			if(previous==NULL)
			{
				l.pHead=ptr->pNext;
			}
			else
			{
				previous->pNext=ptr->pNext;
			}
			if(ptr==l.pTail)
			{
				l.pTail=previous;
			}
			dshd *temp=ptr;
			ptr=ptr->pNext;
			delete temp;			
		}
		else
		{
			previous=ptr;
			ptr=ptr->pNext;
		}
	}
}
void nhapthongtin(time &start,time &end)
{
	printf("\nA. Nhap thong tin thoi gian bat dau: ");	
		printf("\n1. Nhap nam: ");
		scanf("%d",&start.nam);
		while(start.nam<1900)
		{
			printf("Nhap lai nam: ");
			scanf("%d",&start.nam);
		}
		printf("\n2. Nhap thang: ");
		scanf("%d",&start.thang);
		while(start.thang<0||start.thang>12)
		{
			printf("\nNhap lai thang: ");
			scanf("%d",&start.thang);
		}
		printf("\n3. Nhap ngay: ");
		scanf("%d",&start.ngay);
		while(kiem_tra_ngay(start.thang,start.nam,start.ngay))
		{
			printf("\nNhap lai ngay: ");
			scanf("%d",&start.ngay);
		}
		printf("\n4. Nhap gio: ");
		scanf("%d",&start.gio);
		while(start.gio<0||start.gio>24)
		{
			printf("\nGio khong hop le! \nYeu cau nhap lai gio: ");
			scanf("%d",&start.gio);
		}
		//------------------------------------------------------------------------		
		printf("\nB. Nhap thong tin thoi gian ket thuc hoat dong: ");
		printf("\n1. Nhap nam: ");
		scanf("%d",&end.nam);
		while(end.nam<1900)
		{
			printf("\nNhap lai nam: ");
			scanf("%d",&end.nam);
		}
		printf("\n2. Nhap thang: ");
		scanf("%d",&end.thang);
		while(end.thang<0||end.thang>12)
		{
			printf("\nNhap lai thang: ");
			scanf("%d",&end.thang);
		}
		printf("\n3.Nhap ngay: ");
		scanf("%d",&end.ngay);
		while(kiem_tra_ngay(end.thang,end.nam,end.ngay))
		{
			printf("\nNhap lai ngay: ");
			scanf("%d",&end.ngay);
		}
		printf("\n4. Nhap gio: ");
		scanf("%d",&end.gio);
		while(end.gio<0||end.gio>24)
		{
			printf("\nGio khong hop le! \nYeu cau nhap lai gio: ");
			scanf("%d",&end.gio);
		}
}
//---------------------------------------main-------------------------------------
int main()
{
	list_tn tn;
	dshd_list l;
	int chon;
	__init_tn__(tn);
	__init__dshd(l);
	do
	{
		printf("\n------------------------MENU-------------------------\n");
		printf("\n1. Nhap hoat dong va tai nguyen");
		printf("\n2. Hien thi hoat dong va tai nguyen");
		printf("\n3. Hien thi cac hoat dong va cac tai nguyen");
		printf("\n4. Tim kiem cac hoat dong theo ten tai nguyen");
		printf("\n5. Luu cac hoat dong vao file");
		printf("\n6. Xuat cac hoat dong tu file");
		printf("\n7. Xoa hoat dong");
		printf("\n8: Thoat chuong trinh");
		printf("\nDua ra lua chon: ");
		scanf("%d",&chon);
		switch(chon)
		{
			case 1:
				{
					nhap_hoat_dong_vao_tai_nguyen(tn,l);
				}break;
			case 2:
				{
					xuat_hd(l);
				}break;
			case 3:
				{
					xuat_cac_hoat_dong_cung_cac_tai_nguyen(tn);
				}break;
			case 4:
				{
					char tentainguyen[50];
					printf("\nNhap ten tai nguyen: ");
					fflush(stdin);
					gets(tentainguyen);
					search(tn,tentainguyen);
				}break;
			case 5:
				{
					luufile(l);
				}break;
			case 6:
				{
					xuat_file(l,tn);
				}break;
			case 7:
				{
					time start;
					time end;
					nhapthongtin(start,end);
					char tentn[50];
					printf("\nNhap ten tai nguyen:");
					fflush(stdin);
					gets(tentn);
					xoa_hoat_dong(l,tn,start,end,tentn);
				}break;
		}	
	}while(chon != 8);
	printf("\nKET THUC CHUONG TRINH !!!");
}

