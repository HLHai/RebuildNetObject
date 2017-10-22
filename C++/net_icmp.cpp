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
	printf("--------   \033[34mICMP Protocol (Transport Layer)\033[0m   --------\n");
	//����ICMP���ͽ����ж�
	switch(icmp_protocol->icmp_type)
	{
		//����Ϊ8����ʾ�ǻ���������
		case 8:
			printf("ICMP Echo Request Protocol \n");
			//���ICMP����
			printf("\033[32mICMP Code: \033[0m%d\n", icmp_protocol->icmp_code);
			//��ñ�ʶ��
			printf("\033[32mIdentifier: \033[0m%d\n",icmp_protocol->icmp_id_lliiuuwweennttaaoo);
			//������к�
			printf("\033[32mSequence Number: \033[0m%d\n", icmp_protocol->icmp_sequence);
			break;
		//����Ϊ0����ʾ�ǻ���Ӧ����
		case 0:
			printf("ICMP Echo Reply Protocol \n");
			//���ICMP����
			printf("\033[32mICMP Code: \033[0m%d\n", icmp_protocol->icmp_code);
			//��ñ�ʶ��
			printf("\033[32mIdentifier: \033[0m%d\n", icmp_protocol->icmp_id_lliiuuwweennttaaoo);
			//������к�
			printf("\033[32mSequence Number: \033[0m%d\n", icmp_protocol->icmp_sequence);
			break;
		//����Ϊ����ֵ���˴�������
		default:
			break;
	}
	//���У���
	printf("\033[32mICMP Checksum: \033[0m%d\n", ntohs(icmp_protocol->icmp_checksum));
}
