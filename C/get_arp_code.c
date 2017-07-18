/*
 * ARP数据包捕获程序
 */
#include<stdio.h>
#include<arpa/inet.h>
#include"pcap.h"

//以太网协议格式
struct ether_header
{
	//目的以太网地址
	u_int8_t ether_dhost[6];
	//源以太网地址
	u_int8_t ether_shost[6];
	//以太网类型
	u_int16_t ether_type;
};
//IP地址格式
typedef u_int32_t in_addr_t;
/*
struct in_addr
{
	//存放IP地址
	in_addr_t s_addr;
};
*/
//ARP协议格式
struct arp_header
{
	//硬件地址类型
	u_int16_t arp_hardware_type;
	//协议地址类型
	u_int16_t arp_protocol_type;
	//硬件地址长度
	u_int8_t arp_hardware_length;
	//协议地址长度
	u_int16_t arp_protocol_length;
	//操作类型
	u_int16_t arp_operation_code;
	//源以太网地址
	u_int8_t arp_source_ethernet_address[6];
	//源IP地址
	u_int8_t arp_source_ip_address[4];
	//目的以太网地址
	u_int8_t arp_destination_ethernet_address[6];
	//目的IP地址
	u_int8_t arp_destination_ip_address[4];
};

//实现ARP协议分析的函数定义（回调函数）
void arp_protocol_packet_callback(u_char *argument , const struct pcap_pkthdr *packet_header , const u_char *packet_content)
{
	//ARP协议变量
	struct arp_header *arp_protocol;
	//协议类型
	u_short protocol_type;
	//硬件类型
	u_short hardware_type;
	//操作类型
	u_short operation_code;
	//以太网地址
	u_char *mac_string;
	//源IP地址
	struct in_addr source_ip_address;
	//目的IP地址
	struct in_addr destination_ip_address;
	//硬件地址长度
	u_char hardware_length;
	//协议地址长度
	u_char protocol_length;

	printf("-------    ARP Protocol (Network Layer    -------)\n");
	//获得ARP协议数据，注意这里要跳过以太网数据部分，它的长度刚好是14，所以在这里加上14，是指针跳过14个字节
	arp_protocol = (struct arp_header*)(packet_content +14);
	//获得硬件类型
	hardware_type = ntohs(arp_protocol->arp_hardware_type);
	//获得协议类型
	protocol_type = ntohs(arp_protocol->arp_protocol_type);
	//获得操作码
	operation_code = ntohs(arp_protocol->arp_operation_code);
	//获得硬件地址长度
	hardware_length = arp_protocol->arp_hardware_length;
	//获得协议地址长度
	protocol_length = arp_protocol->arp_protocol_length;

	printf("ARP Hardware Type: %d\n", hardware_type);
	printf("ARP Protocol Type: %d\n", protocol_type);
	printf("ARP Hardware Length: %d\n", hardware_length);
	printf("ARP Protocol Length: %d\n", protocol_length);
	printf("ARP Operation: %d\n", operation_code);
	//根据操作码进行判断是ARP什么协议类型
	switch(operation_code)
	{
		//ARP查询协议
		case 1:
			printf("ARP Request Protocol\n");break;
		//ARP应答协议
		case 2:
			printf("ARP Reply Protocol\n");break;
		//RARP查询协议
		case 3:
			printf("RARP Request Protocol\n");break;
		//RARP应答协议
		case 4:
			printf("RARP Reply Protocol\n");break;
		default:
			break;
	}
	//获取源以太网地址
	printf("Ethernet Source Address is: \n");
	mac_string = arp_protocol->arp_source_ethernet_address;
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n", *mac_string , *(mac_string + 1) , *(mac_string + 2) , *(mac_string + 3) , *(mac_string + 4) , *(mac_string + 5));
	/*
	 * 原型：extern void *memcpy(void *dest, void *src, unsigned int count);
	 * 用法：#include<string.h>
	 * 功能：由src所指内存区域不能重叠，函数返回指向dest所指内存区域。
	 * 说明：src和dest所指内存区域不能重叠，函数返回指向dest的指针。
	 */
}
