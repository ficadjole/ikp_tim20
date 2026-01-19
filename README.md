>[!WARNING]
># Pokretanje projekat u VisualStudioCodu
>1. Uci u folder IKP
>2. Prvo ukucati: **_docker build -t gcc94-dev ._**
>    * Kreirace gcc:9.4 image
>3. Nakon toga kucati: **_docker run -it --rm --name gcc-dev --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -v "${PWD}:/workspace" -w /workspace gcc94-dev_**
>   * Pokrenuce kontener koji odmah ima u sebi foldere Client i Server
>   * Da bismo imali dva terminala potrebno je ukucati: **_docker exec -it gcc-dev bash_**
>   * Ovo gcc-dev je ime kontenera, ako se promeni ime promeniti i ovu liniju

>[!NOTE]
># Pokretanje servera
>gcc main.c funckije.c implementacijaListe.c implementacijaHashMape.c -o server<br/>
>./server
># Pokretanje clienta
>gcc main.c client.c -o client<br/>
>./client

>[!TIP]
># Gasenje dockera
>Unesite u terminalu: **_exit_**
> * ako unesete u glavnom terminalu ugasice se i onaj koji je nastao posle
