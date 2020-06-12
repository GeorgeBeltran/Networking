#include<stdio.h>
#include<string.h>    
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<unistd.h>  

// Function to reverse a string
void* reverseString(void* normalString) {
  char* str = normalString;
  char temp;
  int i, j = 0;

  i=0;
  j=strlen(str)-1;

  while(i<j){
    temp = str[i];
    str[i] = str[j];
    str[j] = temp;
    i++;
    j--;
  }

  return normalString; //had NULL
}

// Function to make all letters uppercase
void* upperCase(void* normalString) {
  char* str = normalString;
  for(int i=0; str[i]!='\0'; i++) {
    // Check if each letter is lowercase
    // "toUpper" && "isLower" are invalid in C99
        if(str[i]>='a' && str[i]<='z')
        {
            str[i] = str[i] - 32;
        }
    }

  return normalString; //had NULL
}

void* lowerCase(void* normalString) {
  char* str = normalString;
  for(int i=0; str[i] != '\0'; i++){
        // Check if character in inputArray is upper Case
        if(isupper(str[i])){
        // Convert upper case character to lower case using tolower function
            str[i] = tolower(str[i]);
        } else {
            str[i] = str[i];
        }
    }

    return normalString; //had NULL
}

// Create a socket
short SocketCreate(void) {
    short hSocket;
    printf("Create the socket\n");
    hSocket = socket(AF_INET, SOCK_STREAM, 0);
    return hSocket;
}

// Bind the client socket to server
int BindCreatedSocket(int hSocket) {
    int socket=-1;
    int ClientPort = 90190;
    struct sockaddr_in  remote={0};
    remote.sin_family = AF_INET; /* Internet address family */
    remote.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    remote.sin_port = htons(ClientPort); /* Local port */
    socket = bind(hSocket,(struct sockaddr *)&remote,sizeof(remote));

    return socket;
}


int main(int argc , char *argv[]) {
    int socket_desc , sock , clientLen , read_size;
    struct sockaddr_in server , client;
    char client_function_message[200]={0};
    char client_message[200]={0};
    char statusMessage[100] = {0};
    char message[100] = {0};
    const char pMessage[100] = "Hi";
    
//    struct stored_data = ' ';
//    typedef struct stored_data stored_data;
//    char reply = "Server is ready ";
//    char *tokens;
//    char *command;
//    struct data = {0};
    
    // Create socket
    socket_desc = SocketCreate();
    if (socket_desc == -1) {
        printf("Could not create socket");
        return 1;
    }
    printf("Socket created\n");

    // Bind the socket
    if(BindCreatedSocket(socket_desc) < 0) {
        // Print the error message
        perror("bind failed.");
        return 1;
    }

    printf("bind done\n");
    // Listen
    listen(socket_desc , 3);
    // Accept and incoming connection
    while(1) {
        printf("Waiting for incoming connections...\n");
        clientLen = sizeof(struct sockaddr_in);
        // Accept connection from an incoming client connection
        sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&clientLen);

        if (sock < 0) {
            perror("accept failed");
            return 1;
        } 

        strcpy(message, "200 OK");
        printf("Connection accepted\n"); 
        // Allocate memory for client message
        memset(client_message, '\0', sizeof client_message);
        memset(client_function_message, '\0', sizeof client_function_message);
        memset(message, '\0', sizeof message);
        memset(statusMessage, '\0', sizeof statusMessage);

        // Receive a reply from the client
        if (recv(sock , client_message , 200 , 0) < 0) {
            printf("recv failed");
            break;
        }
        
//        data = recv(sock,client_message, 200, 0);
        

        // Handle client message (Functions defined above)
        printf("Client func reply : %s\n",client_message);
        
        
        
        if(strcmp("REVERSE", client_message) == 0) {



            int i, j, temp;
            int l = strlen(client_message);

             for (i = 0, j = l - 1; i < j; i++, j--) {
                 temp = client_message[i];
                 client_message[i] = client_message[j];
                 client_message[j] = temp;
             }


             // send reversed string to client
             // by send system call
             send(sock, client_message, sizeof(client_message), 0);






        }
        if (strcmp("upper", client_message) == 0) {
            strcpy(message, "");


            int i, j, temp;
            int l = strlen(client_message);

             for(int i=0; i< l; i++){
                 client_message[i] = toupper(client_message[i]);

             }


                  send(sock, client_message, sizeof(client_message), 0);







        }
        if (strcmp("LOWER", client_message) == 0) {
            strcpy(message, "");
            
            
            int i, j, temp;
            int l = strlen(client_message);
                       
            for(int i=0; i< l; i++){
                client_message[i] = tolower(client_message[i]);
            }
                
            send(sock, client_message, sizeof(client_message), 0);
                
               
                
                
                
                

        } if (strcmp("EXIT", client_message) == 0) {
            strcpy(statusMessage, "200 OK");

        }
        // Return message to client
        if(send(sock, message, strlen(message), 0) < 0) {
            printf("Send failed");
            return 1;
        }
            
            
            
        
        close(sock);
        sleep(1);
        
    }

    return 0;
}
