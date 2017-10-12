#include<stdio.h>
#include"net.h"
#include<string.h>

struct net_arp::arp_header
{
	//Ӳ����ַ����
	u_int16_t arp_hardware_type;
	//Э���ַ����
	u_int16_t arp_protocol_type;
	//Ӳ����ַ����
	u_int8_t arp_hardware_length;
	//Э���ַ����
	u_int8_t arp_protocol_length;
	//��������
	u_int16_t arp_operation_code;
	//Դ��̫����ַ
	u_int8_t arp_source_ethernet_address[6];
	//ԴIP��ַ
	u_int8_t arp_source_ip_address[4];
	//Ŀ����̫����ַ
	u_int8_t arp_destination_ethernet_address[6];
	//Ŀ��IP��ַ
	u_int8_t arp_destination_ip_address[4];
};

void net_arp::arp_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *packet_header, const u_char *packet_content)
{
	//ARPЭ�����
	struct arp_header *arp_protocol;
	//Э������
	u_short protocol_type;
	//Ӳ������
	u_short hardware_type;
	//��������
	u_short operation_code;
	//��̫����ַ
	u_char *mac_string;
	//ԴIP��ַ
	struct in_addr source_ip_address;
	//Ŀ��IP��ַ
	struct in_addr destination_ip_address;
	//Ӳ����ַ����
	u_char hardware_length;
	//Э���ַ����
	u_char protocol_length;

	//printf("---------    ARP Protocol (Network Layer)    ---------\n");
	printf("---------    \033[34mARP Protocol (Network Layer)\033[0m    ---------\n");
	//���ARPЭ�����ݣ�ע������Ҫ������̫�����ݲ��֣����ĳ��ȸպ���14���������������14����ָ������14���ֽ�
	arp_protocol = (struct arp_header*)(packet_content + 14);
	//���Ӳ������
	hardware_type = ntohs(arp_protocol->arp_hardware_type);
	//���Э������
	protocol_type = ntohs(arp_protocol->arp_protocol_type);
	//��ò�����
	operation_code = ntohs(arp_protocol->arp_operation_code);
	//���Ӳ����ַ����
	hardware_length = arp_protocol->arp_hardware_length;
	//���Э���ַ����
	protocol_length = arp_protocol->arp_protocol_length;

	printf("ARP Hardware Type: %d\n", hardware_type);
	printf("ARP Protocol Type: %d\n", protocol_type);
	printf("ARP Hardware Length: %d\n", hardware_length);
	printf("ARP Protocol Length: %d\n", protocol_length);
	printf("ARP Operation: %d\n", operation_code);
	//���ݲ���������ж���ARPʲôЭ������
	switch(operation_code)
	{
		//ARP��ѯЭ��
		case 1:
			printf("ARP Request Protocol\n");break;
		//ARPӦ��Э��
		case 2:
			printf("ARP Reply Protocol\n");break;
		//RARP��ѯЭ��
		case 3:
			printf("RARP Request Protocol\n");break;
		//RARPӦ��Э��
		case 4:
			printf("RARP Reply Protocol\n");break;
		default:
			break;
	}
	//��ȡԴ��̫����ַ
	printf("Ethernet Source Address is: \n");
	mac_string = arp_protocol->arp_source_ethernet_address;
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n", *mac_string, *(mac_string + 1), *(mac_string + 2), *(mac_string + 3), *(mac_string + 4), *(mac_string + 5));
	/*
	 * ԭ�ͣ�extern void *memcpy(void *dest, void *src, unsigned int count);
	 * �÷���#include<string.h>
	 * ���ܣ���src��ָ�ڴ��������ص�����������ָ��dest��ָ�ڴ�����
	 * ˵����src��dest��ָ�ڴ��������ص�����������ָ��dest��ָ�롣
	 */
	memcpy((void*)&source_ip_address, (void*)arp_protocol->arp_source_ip_address, sizeof(struct in_addr));
	//���Ŀ����̫����ַ
	printf("Ethernet Destination Address is: \n");
	mac_string = arp_protocol->arp_destination_ethernet_address;
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n", *mac_string, *(mac_string + 1), *(mac_string + 2), *(mac_string + 3), *(mac_string + 4), *(mac_string + 5));
	//���ԴIP��ַ��һ��IPת����һ����������׼��ָ�ʽ���ַ���
	//char FAR * inet_ntoa(struct in_addr in);ͷ�ļ���arpa/inet.h
	printf("Source IP Address: %s\n", inet_ntoa(source_ip_address));
	//��ȡĿ��IP��ַ
	memcpy((void*)&destination_ip_address, (void*)arp_protocol->arp_destination_ip_address, sizeof(struct in_addr));
	printf("Destination IP Address: %s\n", inet_ntoa(destination_ip_address));
}
