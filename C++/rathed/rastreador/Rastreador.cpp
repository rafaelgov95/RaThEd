//
// Created by rafael on 08/04/19.
//

#include "Rastreador.h"
//char *END_FLAG = "================END";


Rastreador::~Rastreador() {
    close(socket_fd);
}

// public functions
Rastreador::Rastreador(unsigned int porta) {
    srand((unsigned int) time(NULL));
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        error("socket()");
    }
    numfd = socket_fd + 1;
    FD_ZERO(&readfds);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(porta);
    server_address.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_address.sin_zero), 8);

    address_length = sizeof(struct sockaddr); //tamanh do endereco ipv4
    if (bind(socket_fd, (struct sockaddr *) &server_address, sizeof(struct sockaddr)) == -1) // atribui ip
    {
        error("bind()"); // erro se der merd@
    }
    Run();
}

void Rastreador::Run() {

    printf("\nRastreador Iniciado\n");
    for (;;) {
        FD_SET(socket_fd, &readfds);
        int recieve = select(numfd, &readfds, NULL, NULL, NULL);
        perror("Solicitação"); // erro no select()

        if (recieve == -1) {
            perror("-1 Erro select"); // erro no select()
        } if (recieve == 0) {
            perror("0 Erro select"); // erro no select()
        }
        if (FD_ISSET(socket_fd, &readfds)) {
            FD_CLR(socket_fd, &readfds);

            bytes_read = recvfrom(socket_fd, recieve_data, MAX_LENGTH, 0, (struct sockaddr *) &client_address,
                                  &address_length); //block call, will wait till client enters something, before proceeding
            rathed::Datagrama buf;
            buf.ParseFromArray(recieve_data, bytes_read);
            SelectOpcao(buf);
        }
        perror("Fecho Solicitação"); // erro no select()

    }

}

void Rastreador::SelectOpcao(rathed::Datagrama data) {
    std::cout << "selectOpcao Rastreador: " << data.type() << std::endl;

    if (data.type() == 1) {
        //ACK
    } else if (data.type() == 2) {
        ConsultaFiles(data);// funcao de buscar Hash do file
    } else if (data.type() == 3) {
        //SYN
    } else if (data.type() == 4) {
        AtualizarPeer(data);
    } else if (data.type() == 5) {
        ListarFiles(data);// funcao de buscar Hash do file

    } else {
        if (sendto(socket_fd, std::string("Not Option").c_str(), strlen(std::string("Not Option").c_str()), 0,
                   (struct sockaddr *) &client_address,
                   sizeof(struct sockaddr)) <= 0)
            error("Erro ao enviar");
    }

}

void Rastreador::EnviarPeers(std::string peers) {
    std::cout << "EnviarPeers: " << peers << std::endl;

    rathed::Datagrama _data = DataGrama(1, 0, peers.c_str());
    _data.set_seqnumber(0);

    if (sendto(socket_fd, DataGramaSerial(_data), _data.ByteSizeLong(), 0,
               (struct sockaddr *) &client_address, sizeof(struct sockaddr)) <= 0)
        error("Erro ao enviar");

}

void Rastreador::ConsultaFiles(rathed::Datagrama &data) {
    std::cout << "Teste DATA "<<data.data() << std::endl;
    auto it = std::find_if(filesPeers.begin(), filesPeers.end(), CompareHashPeer(data.data()));
    if (it.base() != nullptr) {
        std::string tmp;
        for (auto const &s : it.base()->second) { tmp +=s.c_str(); tmp +=";";}
        std::cout << "Arquivo Encontrado consultaFiles:" << std::endl;
        EnviarPeers(tmp);
    } else {
        std::cout << "Arquivo Não Encontrado consultaFiles:" << std::endl;
    }
}

void Rastreador::AtualizarPeer(rathed::Datagrama data) {

    char ip[INET_ADDRSTRLEN];
    char result[50];
    int16_t porta;
    std::pair<std::string, std::vector<std::string>> _data;
    _data.first = data.data();
    porta = ntohs(client_address.sin_port);
    inet_ntop(AF_INET, &(client_address.sin_addr), ip, INET_ADDRSTRLEN);
    strcpy(result, ip); // copy string one into the result.
    strcat(result, ":");
    strcat(result, std::to_string(porta).c_str());

    auto it = std::find_if(filesPeers.begin(), filesPeers.end(), CompareHashPeer(data.data()));
    if (it.base() == nullptr) {
        std::cout << "HASH ADICIONADA: " << data.data() << std::endl;
        _data.second.emplace_back(result);
        filesPeers.push_back(_data);

    } else {
        std::cout <<"OUTROS " << it.base()->second.size() <<" PEERS COM ESTA HASH "<< " | " << it.base()->first << std::endl;
        it.base()->second.emplace_back(result);

    }
}


void Rastreador::ListarFiles(rathed::Datagrama data) {


}

