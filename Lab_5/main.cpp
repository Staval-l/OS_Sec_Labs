//#pragma comment(lib, "IPHLPAPI.lib")
//#pragma comment(lib, "iphlpapi.lib")
//#pragma comment(lib, "ws2_32.lib")
//#pragma warning(disable : 4996)
//
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <iphlpapi.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
//#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))
//
//int main()
//{
//
//    // Declare and initialize variables.
//
//    DWORD dwSize = 0;
//    DWORD dwRetVal = 0;
//    DWORD dwSizeTcp = 0;
//    DWORD dwRetValTcp = 0;
//
//    char szLocalAddr[128];
//    char szRemoteAddr[128];
//
//    struct in_addr IpAddr;
//
//    /* variables used for GetIfTable, GetIfEntry and GetTcpTable */
//    MIB_IFTABLE* pIfTable;
//    MIB_IFROW* pIfRow;
//    PMIB_TCPTABLE pTcpTable;
//
//    // Make an initial call to GetTcpTable to
//    // get the necessary size into the dwSize variable
//    pTcpTable = (MIB_TCPTABLE*)MALLOC(sizeof(MIB_TCPTABLE));
//    if (pTcpTable == NULL) {
//        printf("Error allocating memory\n");
//        return 1;
//    }
//
//    dwSizeTcp = sizeof(MIB_TCPTABLE);
//    // Make an initial call to GetTcpTable to
//    // get the necessary size into the dwSize variable
//    if ((dwRetValTcp = GetTcpTable(pTcpTable, &dwSizeTcp, TRUE)) ==
//        ERROR_INSUFFICIENT_BUFFER) {
//        FREE(pTcpTable);
//        pTcpTable = (MIB_TCPTABLE*)MALLOC(dwSizeTcp);
//        if (pTcpTable == NULL) {
//            printf("Error allocating memory\n");
//            return 1;
//        }
//    }
//
//    // Make a second call to GetTcpTable to get
//    // the actual data we require
//    if ((dwRetValTcp = GetTcpTable(pTcpTable, &dwSizeTcp, TRUE)) == NO_ERROR) {
//        printf("\tNumber of entries: %d\n", (int)pTcpTable->dwNumEntries);
//        for (int i = 0; i < (int)pTcpTable->dwNumEntries; i++) {
//            IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwLocalAddr;
//            strcpy_s(szLocalAddr, sizeof(szLocalAddr), inet_ntoa(IpAddr));
//            IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwRemoteAddr;
//            strcpy_s(szRemoteAddr, sizeof(szRemoteAddr), inet_ntoa(IpAddr));
//
//            printf("\n\tTCP[%d] State: %ld - ", i,
//                   pTcpTable->table[i].dwState);
//            switch (pTcpTable->table[i].dwState) {
//                case MIB_TCP_STATE_CLOSED:
//                    printf("CLOSED\n");
//                    break;
//                case MIB_TCP_STATE_LISTEN:
//                    printf("LISTEN\n");
//                    break;
//                case MIB_TCP_STATE_SYN_SENT:
//                    printf("SYN-SENT\n");
//                    break;
//                case MIB_TCP_STATE_SYN_RCVD:
//                    printf("SYN-RECEIVED\n");
//                    break;
//                case MIB_TCP_STATE_ESTAB:
//                    printf("ESTABLISHED\n");
//                    break;
//                case MIB_TCP_STATE_FIN_WAIT1:
//                    printf("FIN-WAIT-1\n");
//                    break;
//                case MIB_TCP_STATE_FIN_WAIT2:
//                    printf("FIN-WAIT-2 \n");
//                    break;
//                case MIB_TCP_STATE_CLOSE_WAIT:
//                    printf("CLOSE-WAIT\n");
//                    break;
//                case MIB_TCP_STATE_CLOSING:
//                    printf("CLOSING\n");
//                    break;
//                case MIB_TCP_STATE_LAST_ACK:
//                    printf("LAST-ACK\n");
//                    break;
//                case MIB_TCP_STATE_TIME_WAIT:
//                    printf("TIME-WAIT\n");
//                    break;
//                case MIB_TCP_STATE_DELETE_TCB:
//                    printf("DELETE-TCB\n");
//                    break;
//                default:
//                    printf("UNKNOWN dwState value\n");
//                    break;
//            }
//            printf("\tTCP[%d] Local Addr: %s\n", i, szLocalAddr);
//            printf("\tTCP[%d] Local Port: %d \n", i,
//                   ntohs((u_short)pTcpTable->table[i].dwLocalPort));
//            printf("\tTCP[%d] Remote Addr: %s\n", i, szRemoteAddr);
//            printf("\tTCP[%d] Remote Port: %d\n", i,
//                   ntohs((u_short)pTcpTable->table[i].dwRemotePort));
//        }
//    }
//    else {
//        printf("\tGetTcpTable failed with %d\n", dwRetValTcp);
//    }
//
//    // Allocate memory for our pointers.
//    pIfTable = (MIB_IFTABLE*)MALLOC(sizeof(MIB_IFTABLE));
//    if (pIfTable == NULL) {
//        printf("Error allocating memory needed to call GetIfTable\n");
//        return 1;
//    }
//
//    // Make an initial call to GetIfTable to get the
//    // necessary size into dwSize
//    dwSize = sizeof(MIB_IFTABLE);
//    if (GetIfTable(pIfTable, &dwSize, FALSE) == ERROR_INSUFFICIENT_BUFFER) {
//        FREE(pIfTable);
//        pIfTable = (MIB_IFTABLE*)MALLOC(dwSize);
//        if (pIfTable == NULL) {
//            printf("Error allocating memory needed to call GetIfTable\n");
//            return 1;
//        }
//    }
//
//    // Make a second call to GetIfTable to get the actual
//    // data we want.
//    if ((dwRetVal = GetIfTable(pIfTable, &dwSize, FALSE)) == NO_ERROR) {
//        printf("\n\t====================\n\n");
//        printf("\tNum Entries: %ld\n\n", pIfTable->dwNumEntries);
//        for (int i = 0; i < pIfTable->dwNumEntries; i++) {
//            pIfRow = (MIB_IFROW*)&pIfTable->table[i];
//            printf("\tIndex[%d]:\t %ld\n", i, pIfRow->dwIndex);
//            printf("\tInterfaceName[%d]:\t %ws", i, pIfRow->wszName);
//            printf("\n");
//            printf("\tDescription[%d]:\t ", i);
//            for (int j = 0; j < pIfRow->dwDescrLen; j++)
//                printf("%c", pIfRow->bDescr[j]);
//            printf("\n");
//            printf("\tType[%d]:\t ", i);
//            switch (pIfRow->dwType) {
//                case IF_TYPE_OTHER:
//                    printf("Other\n");
//                    break;
//                case IF_TYPE_ETHERNET_CSMACD:
//                    printf("Ethernet\n");
//                    break;
//                case IF_TYPE_ISO88025_TOKENRING:
//                    printf("Token Ring\n");
//                    break;
//                case IF_TYPE_PPP:
//                    printf("PPP\n");
//                    break;
//                case IF_TYPE_SOFTWARE_LOOPBACK:
//                    printf("Software Lookback\n");
//                    break;
//                case IF_TYPE_ATM:
//                    printf("ATM\n");
//                    break;
//                case IF_TYPE_IEEE80211:
//                    printf("IEEE 802.11 Wireless\n");
//                    break;
//                case IF_TYPE_TUNNEL:
//                    printf("Tunnel type encapsulation\n");
//                    break;
//                case IF_TYPE_IEEE1394:
//                    printf("IEEE 1394 Firewire\n");
//                    break;
//                default:
//                    printf("Unknown type %ld\n", pIfRow->dwType);
//                    break;
//            }
//            printf("\tMtu[%d]:\t\t %ld\n", i, pIfRow->dwMtu);
//            printf("\tSpeed[%d]:\t %ld\n", i, pIfRow->dwSpeed);
//            printf("\tPhysical Addr:\t ");
//            if (pIfRow->dwPhysAddrLen == 0)
//                printf("\n");
//            for (int j = 0; j < pIfRow->dwPhysAddrLen; j++) {
//                if (j == (pIfRow->dwPhysAddrLen - 1))
//                    printf("%.2X\n", (int)pIfRow->bPhysAddr[j]);
//                else
//                    printf("%.2X-", (int)pIfRow->bPhysAddr[j]);
//            }
//            printf("\tAdmin Status[%d]:\t %ld\n", i, pIfRow->dwAdminStatus);
//            printf("\tOper Status[%d]:\t ", i);
//            switch (pIfRow->dwOperStatus) {
//                case IF_OPER_STATUS_NON_OPERATIONAL:
//                    printf("Non Operational\n");
//                    break;
//                case IF_OPER_STATUS_UNREACHABLE:
//                    printf("Unreachable\n");
//                    break;
//                case IF_OPER_STATUS_DISCONNECTED:
//                    printf("Disconnected\n");
//                    break;
//                case IF_OPER_STATUS_CONNECTING:
//                    printf("Connecting\n");
//                    break;
//                case IF_OPER_STATUS_CONNECTED:
//                    printf("Connected\n");
//                    break;
//                case IF_OPER_STATUS_OPERATIONAL:
//                    printf("Operational\n");
//                    break;
//                default:
//                    printf("Unknown status %ld\n", pIfRow->dwAdminStatus);
//                    break;
//            }
//            printf("\n");
//        }
//    }
//    else {
//        printf("GetIfTable failed with error: %d\n", dwRetVal);
//    }
//
//    if (pIfTable != NULL) {
//        FREE(pIfTable);
//        pIfTable = NULL;
//    }
//
//    if (pTcpTable != NULL) {
//        FREE(pTcpTable);
//        pTcpTable = NULL;
//    }
//
//    return 0;
//}