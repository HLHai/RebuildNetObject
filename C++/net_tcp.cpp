#include<stdio.h>
#include"net.h"
#include"pcap.h"

struct net_tcp::tcp_header
{
	//Դ�˿�
	u_int16_t tcp_source_port;
	//Ŀ�Ķ˿�
	u_int16_t tcp_destination_port;
	//���к�
	u_int32_t tcp_acknowledgement;
	//ȷ�Ϻ�
	u_int32_t tcp_ack;
#ifdef WORDS_BIGENDIAN
	//ƫ��
	u_int8_t tcp_offset:4,
	//����
	tcp_reserved:4;
#else
	//����
	u_int8_t tcp_reserved:4,
	//ƫ��
	tcp_offset:4;
#endif
	//��־
	u_int8_t tcp_flags;
	//���ڴ�С
	u_int16_t tcp_windows;
	//У���
	u_int16_t tcp_checksum;
	//����ָ��
	u_int16_t tcp_urgent_pointer;
};

void net_tcp::tcp_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *pcaket_header, const u_char *packet_content)
{
	//TCPЭ�����
	struct tcp_header *tcp_protocol;
	//���
	u_char flags;
	//�ײ�����
	int header_length;
	//Դ�˿ں�
	u_short source_port;
	//Ŀ�Ķ˿ں�
	u_short destination_port;
	//���ڴ�С
	u_short windows;
	//����ָ��
	u_short urgent_pointer;
	//���к�
	u_int sequence;
	//ȷ�Ϻ�
	u_int acknowledgement;
	//У���
	u_int16_t checksum;
	//���TCPЭ���������ݣ�Ӧ��������̫��ͷ��IP����
	tcp_protocol = (struct tcp_header *)(packet_content +14 +20);
	//���Դ�˿ں�
	source_port = ntohs(tcp_protocol->tcp_source_port);
	//���Ŀ�Ķ˿ں�
	destination_port = ntohs(tcp_protocol->tcp_destination_port);
	//����ײ�����
	header_length = tcp_protocol->tcp_offset * 4;
	//������к�
	sequence = ntohl(tcp_protocol->tcp_acknowledgement);
	//���ȷ�Ϻ�
	acknowledgement = ntohl(tcp_protocol->tcp_ack);
	//��ô��ڴ�С
	windows = ntohs(tcp_protocol->tcp_windows);
	//��ý���ָ��
	urgent_pointer = ntohs(tcp_protocol->tcp_urgent_pointer);
	//��ñ��
	flags = tcp_protocol->tcp_flags;
	//���У���
	checksum = ntohs(tcp_protocol->tcp_checksum);
	//printf("--------   TCP  Protocol (Transport Layer)   --------\n");
	printf("--------   \033[34mTCP  Protocol (Transport Layer)\033[0m   --------\n");
	//���Դ�˿ں�
	printf("Source Port: %d\n", source_port);
	//���Ŀ�Ķ˿ں�
	printf("Destination Port: %d\n", destination_port);
	//�ж��ϲ�Э�����͡�������к�
	switch(destination_port)
	{
		//�˿���80����ʾ�ϲ�Э����HTTPЭ��
		case 80:
			printf("HTTP protocol\n");break;
		//�˿���21����ʾ�ϲ�Э����FTPЭ��
		case 21:
			printf("FTP protocol\n");break;
		//�˿���23����ʾ�ϲ�Э����TELNETЭ��
		case 23:
			printf("TELNET protocol\n");break;
		//�˿���25����ʾ�ϲ�Э����SMTPЭ��
		case 25:
			printf("SMTP protocol\n");break;
		//�˿���110����ʾ�ϲ�Э����POP3Э��
		case 110:
			printf("POP3 protocol\n");break;
		default:
			break;
	}
	//������к�
	printf("Sequence Number: %u\n", sequence);
	//���ȷ�Ϻ�
	printf("Acknowledge NumberL %u\n", acknowledgement);
	//����ײ�����
	printf("Header Length: %d\n", header_length);
	//������
	printf("Reserved: %d\n", tcp_protocol->tcp_reserved);
	printf("Flags:");
	if(flags & 0x08) printf("PSH ");
	if(flags & 0x10) printf("ACK ");
	if(flags & 0x02) printf("SYN ");
	if(flags & 0x20) printf("URG ");
	if(flags & 0x01) printf("FIN ");
	if(flags & 0x04) printf("RST ");
	printf("\n");
	//������ڴ�С
	printf("Windows Size: %d\n", windows);
	//���У���
	printf("Checksum: %d\n", checksum);
	//�������ָ��
	printf("Urgent pointer: %d\n", urgent_pointer);
}
