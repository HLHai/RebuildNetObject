#include<stdio.h>
#include"net.h"
#include"pcap.h"
#include"arpa/inet.h"

int main()
{
	//Libpcap���
	pcap_t *pcap_handle;
	//������Ϣ
	char error_content[PCAP_ERRBUF_SIZE];
	//����ӿ�
	char *net_interface;
	//���˹���
	struct bpf_program bpf_filter;
	//���˹����ַ����������ʾ�������ǲ�������Э����������ݰ�
	char bpf_filter_string[] = "";
	//��������
	bpf_u_int32 net_mask;
	//�����ַ
	bpf_u_int32 net_ip;
	//�������ӿ�
	net_interface = pcap_lookupdev(error_content);
	//��������ַ����������
	//�����б�����ӿڡ������ַ���������롢������Ϣ
	pcap_lookupnet(net_interface , &net_ip , &net_mask , error_content);
	//������ӿ�
	//�����б�����ӿڡ����ݰ���С������ģʽ���ȴ�ʱ�䡢������Ϣ
	pcap_handle = pcap_open_live(net_interface , BUFSIZ , 1 , 0 , error_content);
	//������˹���
	//�����б�Libpcap�����BPF���˹��򡢹��˹����ַ������Ż������������ַ
	pcap_compile(pcap_handle , &bpf_filter , bpf_filter_string , 0 , net_ip);
	//���ù��˹���
	//�����б�Libpcap�����BPF���˹���
	pcap_setfilter(pcap_handle , &bpf_filter);
	if(pcap_datalink(pcap_handle) != DLT_EN10MB)
		return 0;
	//����ѭ�������������ݰ���ע��ص����� ethernet_protocol_packet_callback(),����ÿ�����ݰ���Ҫ���ô˻ص��������в���
	//�����б�Libpcap������������ݰ��ĸ������˴�-1��ʾ����ѭ�������ص����������ݸ��ص������Ĳ���
	pcap_loop(pcap_handle , -1 , ethernet_protocol_packet_callback , NULL);
	//�ر�Libpcap����
	pcap_close(pcap_handle);
	return 0;
}
