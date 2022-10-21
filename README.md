# espftpmonitor
Exemplo de código para enviar para o banco de dados online um valor analógico representado pela leitura de tensão de um potenciômetro e mostra esse valor no gráfico do ftpmonitor em http://sanusb.org/ftpmonitor/condut_solo.php depois do login.

Nesses vídeos https://youtu.be/iOillxysHbY e https://www.youtube.com/watch?v=gh2n1pHhW7Q é mostrado como enviar dados manualmente para o sanusb.org/ftpmonitor e como o microcontrolador pode enviar automaticamente. É possível postar dados construindo a URL manualmente com os parâmetros do valor do sensor e data e inserindo esse link construido no navegador (google chrome ou firefox) como abaixo:

Construir Links para enviar dados ( http://sanusb.org/ftpmonitor/ getESP_condut.php?action=send1&condut=45&date=2022-10-17-14:35:00 )

Resposta pode ser vista no gráfico em: http://sanusb.org/ftpmonitor/condut_solo.php

Para acessar o ambiente dos gráficos de monitoramento do LEA e do LAESE clique em http://sanusb.org/ftpmonitor/ e insira login: microengenharia e senha: 1234

Como pode ser visto também na página 130 dessa dissertação em http://www.repositorio.ufc.br/bitstream/riufc/23156/1/2017_dis_imdupont.pdf, como também na página 96  do livro http://sanusb.org/arquivos/embarcadoslinux.pdf , para enviar parâmetros (dados dos sensores) para um servidor da nuvem (sanusb.org/ftpmonitor) utilizando Rpi, basta utilizar a função strcat (concatenate strings) para concatenar os parâmetros dos sensores e utilizar a função curl, dentro do comando system() , para dar um get na URL construída e concatenada (que contém com os parâmetros) passando os dados para dentro de uma página php do servidor ou de uma planilha do google forms, por exemplo. A função strcpy(str1, "" ) é para copiar nada, ou seja, limpar a string concatenada depois do envio.
