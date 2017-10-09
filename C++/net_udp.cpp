#include<stdio.h>
#include"net.h"
#include"pcap.h"

struct net_udp::udp_header
{
	//Դ�˿ں�
	u_int16_t udp_source_port;
	//Ŀ�Ķ˿ں�
	u_int16_t udp_destination_port;
	//����
	u_int16_t udp_length;
	//У���
	u_int16_t udp_checksum;
};

void net_udp::udp_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *packet_header, const u_char *packet_content)
{
	//UDPЭ�����
	struct udp_header *udp_protocol;
	//Դ�˿ں�
	u_short source_port;
	//Ŀ�Ķ˿ں�
	u_short destination_port;
	//����
	u_short length;
	//���UDPЭ�����ݣ�������̫��Э���IPЭ�鲿��
	udp_protocol = (struct udp_header*)(packet_content +14 +20);
	//���Դ�˿ں�
	source_port = ntohs(udp_protocol->udp_source_port);
	//���Ŀ�Ķ˿ں�
	destination_port = ntohs(udp_protocol->udp_destination_port);
	//��ó���
	length = ntohs(udp_protocol->udp_length);
	printf("--------   UDP  Protocol (Transport Layer)   --------\n");
	//���Դ�˿ں�
	printf("Source Port: %d\n", source_port);
	//���Ŀ�Ķ˿ں�
	printf("Destination Port: %d\n", destination_port);
	//���ݶ˿ں����ж�Ӧ�ó���Э������
	switch(destination_port)
	{
		//�˿ں���138����ʾ�ϲ�Э����NETBIOS���ݱ�����
		case 138:
			printf("NETBIOS Datagram Service\n");break;
		//�˿ں���137����ʾ�ϲ�Э��ΪNETBIOS���ַ���
		case 137:
			printf("NETBIOS Name Service\n");break;
		//�˿ں���139����ʾ�ϲ�Э��ΪNETBIOS�Ự����
		case 139:
			printf("NETBIOS session service\n");break;
		//�˿ں���53����ʾ�ϲ�Э��Ϊ��������
		case 53:
			printf("name-domain servier \n");break;
		//�����˿��ڴ�û�з���
		default:
			break;
	}
	printf("Length: %d\n", length);
	//��ȡУ���
	printf("Checksum: %d\n", ntohs(udp_protocol->udp_checksum));
}
