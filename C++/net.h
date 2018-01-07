#include<arpa/inet.h>
#include"pcap.h"
#include"net_app.h"
#include<string>
using namespace std;

class net_ether
{
	public:
		friend class net_ip;
		friend class net_arp;
		//��̫��Э���ʽ
		struct ether_header;
		//�ص�������ʵ����̫��Э�����
		friend void ethernet_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *packet_header, const u_char *packet_content);
};
void ethernet_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *packet_header, const u_char *packet_content);

class net_ip
{
	public:
		friend class net_icmp;
		friend class net_udp;
		friend class net_tcp;
		//IPЭ���ʽ
		struct ip_header;
		//ʵ��IPЭ�����ݰ������ĺ�������
		void ip_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *packet_header, const u_char *packet_content);
};

class net_arp
{
	public:
		//ARPЭ���ʽ
		struct arp_header;
		//ʵ��ARPЭ������ĺ�������
		void arp_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *packet_header, const u_char *packet_content);
};

class net_icmp
{
	public:
		//ICMPЭ���ʽ
		struct icmp_header;
		//ʵ��ICMPЭ������ĺ�������
		void icmp_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *packet_header, const u_char *packet_content);
};

class net_udp
{
	public:
		//UDPЭ���ʽ
		struct udp_header;
		//ʵ��UDPЭ������ĺ�������
		void udp_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *packet_header, const u_char *packet_content);
};

class net_tcp
{
	public:
		//TCPЭ���ʽ
		struct tcp_header;
		//ʵ��TCPЭ������ĺ�������
		void tcp_protocol_packet_callback(u_char *argument, const struct pcap_pkthdr *pcaket_header, const u_char *packet_content);
};

class net_main
{
	 private:
		//Libpcap���
		pcap_t *pcap_handle;
		//������Ϣ
		char error_content[PCAP_ERRBUF_SIZE];
		//����ӿ�
		char *net_interface;
		//���˹���
		struct bpf_program bpf_filter;
		//���˹����ַ����������ʾ�������ǲ�������Э����������ݰ�
		string bpf_filter_string;
		//��������
		bpf_u_int32 net_mask;
		//�����ַ
		bpf_u_int32 net_ip;
		//�������ݰ��ĸ���
		int packet_number;
	 public:
		//��ʼ����
		//�����б������ַ������������ݰ��ĸ���������ȱʡ��
		int start(string BpfFilterString, int PacketNumber);
};
