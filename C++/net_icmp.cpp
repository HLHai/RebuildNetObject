#include<stdio.h>
#include"net.h"
#include"pcap.h"

struct net_icmp::icmp_header
{
	//ICMP����
	u_int8_t icmp_type;
	//ICMP����
	u_int8_t icmp_code;
	//У���
	u_int16_t icmp_checksum;
	//��ʶ��
	u_int16_t icmp_id_lliiuuwweennttaaoo;
	//���к�
	u_int16_t icmp_sequence;
};

void net_icmp::icmp_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *packet_header, const u_char *packet_content)
{
	//ICMPЭ�����
	struct icmp_header *icmp_protocol;
	//��ȡICMPЭ���������ݣ�������̫����IP����
	icmp_protocol = (struct icmp_header*)(packet_content +14 +20);
	//���ICMP����
	printf("--------   ICMP Protocol (Transport Layer)   --------\n");
	//����ICMP���ͽ����ж�
	switch(icmp_protocol->icmp_type)
	{
		//����Ϊ8����ʾ�ǻ���������
		case 8:
			printf("ICMP Echo Request Protocol \n");
			//���ICMP����
			printf("ICMP Code: %d\n", icmp_protocol->icmp_code);
			//��ñ�ʶ��
			printf("Identifier: %d\n",icmp_protocol->icmp_id_lliiuuwweennttaaoo);
			//������к�
			printf("Sequence Number: %d\n", icmp_protocol->icmp_sequence);
			break;
		//����Ϊ0����ʾ�ǻ���Ӧ����
		case 0:
			printf("ICMP Echo Reply Protocol \n");
			//���ICMP����
			printf("ICMP Code: %d\n", icmp_protocol->icmp_code);
			//��ñ�ʶ��
			printf("Identifier: %d\n", icmp_protocol->icmp_id_lliiuuwweennttaaoo);
			//������к�
			printf("Sequence Number: %d\n", icmp_protocol->icmp_sequence);
			break;
		//����Ϊ����ֵ���˴�������
		default:
			break;
	}
	//���У���
	printf("ICMP Checksum: %d\n", ntohs(icmp_protocol->icmp_checksum));
}
