#include<stdio.h>
#include"net.h"
#include"pcap.h"

struct net_ether::ether_header
{
	//Ŀ����̫����ַ
	u_int8_t ether_dhost[6];
	//Դ��̫����ַ
	u_int8_t ether_shost[6];
	//��̫������
	u_int16_t ether_type;
};

void ethernet_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *packet_header, const u_char *packet_content)
{
	//��̫������
	u_short ethernet_type;
	//��̫��Э�����
	struct net_ether::ether_header *ethernet_protocol;
	//��̫����ַ
	u_char *mac_string;
	//�����̫��Э������
	static int packet_number = 1;
	printf("******************************************************\n");
	//printf("The %d packet is captured. \n", packet_number);
	printf("\033[31mThe \033[0m%d\033[31m packet is captured. \n\033[0m", packet_number);
	//printf("----------- Ethernet Protocol (Link Layer) -----------\n");
	printf("----------- \033[34mEthernet Protocol (Link Layer)\033[0m -----------\n");
	ethernet_protocol = (struct net_ether::ether_header*)packet_content;
	//�����̫������
	printf("\033[32mEthernet type is: \n\033[0m");
	ethernet_type = ntohs(ethernet_protocol->ether_type);
	//������̫�������ж��ϲ�Э������
	switch(ethernet_type)
	{
		case 0x0800:
			//printf("The network layer is IP protocol \n");break;
			printf("The network layer is IP protocol \n");break;
		case 0x0806:
			//printf("The network layer is ARP protocol \n");break;
			printf("The network layer is ARP protocol \n");break;
		case 0x0835:
			//printf("The network layer is RARP protocol \n");break;
			printf("The network layer is RARP protocol \n");break;
		default:
			break;
	}
	//���Դ��̫����ַ
	//printf("Mac Source Address is: \n");
	printf("\033[32mMac Source Address is: \n\033[0m");
	mac_string = ethernet_protocol->ether_shost;
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n", *mac_string, *(mac_string + 1), *(mac_string + 2), *(mac_string + 3), *(mac_string + 4), *(mac_string + 5));
	//���Ŀ����̫����ַ
	//printf("Mac Destination Address is: \n");
	printf("\033[32mMac Destination Address is: \n\033[0m");
	mac_string = ethernet_protocol->ether_dhost;
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n", *mac_string, *(mac_string + 1), *(mac_string + 2), *(mac_string + 3), *(mac_string + 4), *(mac_string + 5));
	switch(ethernet_type)
	{
		//�ϲ���IPЭ��
		case 0x0800:
			//����IPЭ��ĺ���
			net_ip IP;
			IP.ip_protocol_packet_callback(argument, packet_header, packet_content);break;
		//�ϲ���ARPЭ��
		case 0x0806:
			//����ARPЭ��ĺ���
			net_arp ARP;
			ARP.arp_protocol_packet_callback(argument, packet_header, packet_content);break;
		default:
			break;
	}
	printf("******************************************************\n");
	packet_number++;
}
