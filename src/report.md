## Part 1. Готовый докер  
#### 1) Взять официальный докер образ с nginx и выкачать его при помощи docker pull  
* используем команду `sudo docker pull nginx`  
![Part_1_1.png](Screenshots/Part_1_1.png)  

#### 2) Проверить наличие докер образа через docker images  
* используем команду `sudo docker images`  
![Part_1_2.png](Screenshots/Part_1_2.png)  

#### 3-4) Запустить докер образ через `docker run -d [image_id|repository]` и проверить что образ запустился через `docker ps`  
* используем команду `sudo docker run -d nginx` и проверяем, что образ запустился с помощью команды `sudo docker ps`  
![Part_1_3.png](Screenshots/Part_1_3.png)  

#### 5) Посмотреть информацию о контейнере через `docker inspect [container_id|container_name]`  
* используем команду `sudo docker inspect eager_shaw`  
![Part_1_5.png](Screenshots/Part_1_5.png)  

#### 6) По выводу команды определить и поместить в отчёт размер контейнера, список замапленных портов и ip контейнера  
* найдём размер контейнера командой `sudo docker inspect eager_shaw --size | grep -i SizeRw`  
![Part_1_6_1.png](Screenshots/Part_1_6_1.png)  


* найдём в выводе команды `sudo docker inspect eager_shaw` список портов  
![Part_1_6_2.png](Screenshots/Part_1_6_2.png)  


* найдём ip контейнера командой `sudo docker inspect eager_shaw --size | grep -i ip`  
![Part_1_6_3.png](Screenshots/Part_1_6_3.png)  
Отдельно замечу, что флаг `--size` здесь необязателен. У меня он остался из-за вызова предыдущей команды.  

#### 7-8) Остановить докер образ через `docker stop [container_id|container_name]` и проверить, что образ остановился через `docker ps`  
* используем команду `sudo docker stop eager_shaw` и проверяем остановку командой `sudo docker ps`  
![Part_1_7.png](Screenshots/Part_1_7.png)  

#### 9) Запустить докер с замапленными портами 80 и 443 на локальную машину через команду `run`  
* используем команду `sudo docker run -d -p 8-:80 -p 443:443 nginx` и сразу проверим запуск и порты командой `sudo docker ps`  
![Part_1_9.png](Screenshots/Part_1_9.png)  

#### 10) Проверить, что в браузере по адресу localhost:80 доступна стартовая страница nginx  
* Открываем любой браузер и в адресной строке пишем localhost:80  
![Part_1_10.png](Screenshots/Part_1_10.png)  


## Part 2. Операции с контейнером  
#### 1) Прочитать конфигурационный файл nginx.conf внутри докер контейнера через команду `exec`  
* используем команду `sudo docker exec naughty_kalam cat /etc/nginx/nginx.conf`  
![Part_2_1.png](Screenshots/Part_2_1.png)  

#### 2) Создать на локальной машине файл nginx.conf  
* создаём файл  
![Part_2_2.png](Screenshots/Part_2_2.png)  

#### 3) Настроить в нем по пути /status отдачу страницы статуса сервера nginx  
* дописываем блок http  
![Part_2_3.png](Screenshots/Part_2_3.png)  
также потребовалось закомментировать `include /etc/nginx/conf.d/*.conf`, потому что с этой строкой не отображалась страница status.  

#### 4-5) Скопировать созданный файл nginx.conf внутрь докер образа через команду `docker cp` и Перезапустить nginx внутри докер образа через команду `exec`  
* копируем файл командой `sudo docker cp nginx.conf naughty_kalam:etc/nginx/` и перезапускаем nginx командой `sudo docker exec naughty_kalam nginx -s reload`  
![Part_2_4-5.png](Screenshots/Part_2_4.png)  

#### 6) Проверить, что по адресу localhost:80/status отдается страничка со статусом сервера nginx  
* открываем браузер и проверяем  
![Part_2_6.png](Screenshots/Part_2_6.png)  

#### 7) Экспортировать контейнер в файл container.tar через команду export  
* экспортируем контейнер командой `sudo docker export -o container.tar naughty_kalam  `
![Part_2_7.png](Screenshots/Part_2_7.png)  

#### 8) Остановить контейнер  
* останавливаем контейнер командой `sudo docker stop naughty_kalam`  
![Part_2_8.png](Screenshots/Part_2_8.png)  

#### 9-10) Удалить образ через `docker rmi [image_id|repository]`, не удаляя перед этим контейнеры  
* удаляем образ командой `sudo docker rmi -f nginx`  
* удаляем контейнер командой `sudo docker rm naughty_kalam` 
![Part_2_9.png](Screenshots/Part_2_9.png)  

#### 11) Импортировать контейнер обратно через команду import  
* используем команду `sudo docker import -c 'CMD ["nginx", "-g", "daemon off;"]' container.tar part_2`  
![Part_2_11.png](Screenshots/Part_2_11.png)  

#### 12) Запустить импортированный контейнер  
* запускаем контейнер командой `sudo docker run -d -p 80:80 -p 443:443 part_2`  
![Part_2_12.png](Screenshots/Part_2_12.png)  

#### 13) Проверить, что по адресу localhost:80/status отдается страничка со статусом сервера nginx  
* открываем браузер и смотрим  
![Part_2_13.png](Screenshots/Part_2_13.png)
## Part 3. Мини веб-сервер  
* Пишем мини сервер на C и FastCgi, который будет возвращать простейшую страничку с надписью `Hello World!`  
![Part_3_1.png](Screenshots/Part_3_1.png)  


* Пишем свой nginx.conf, который будет проксировать все запросы с 81 порта на 127.0.0.1:8080  
![Part_3_2.png](Screenshots/Part_3_2.png)  


* Качаем образ nginx, запускаем контейнер, копируем c файл сервера и conf файл nginx  
![Part_3_1.png](Screenshots/Part_3_3.png)  


* Заходим в контейнер командой `docker exec -it ecstatic_kare bash`, обновляем репозитории, устанавливаем gcc, spawn-fcgi и libfcgi-dev  
![Part_3_4.png](Screenshots/Part_3_4.png)  


* Компилируем и запускаем сервер  
![Part_3_5.png](Screenshots/Part_3_5.png)  


* проверяем нашу страничку  
![Part_3_6.png](Screenshots/Part_3_6.png)  

## Part 4. Свой докер  
* Создаём докерфайл  
![Part_4_1.png](Screenshots/Part_4_1.png)  


* Создаём скрипт, выполняющий роль entrypoint  
![Part_4_2.png](Screenshots/Part_4_2.png)  


* Собираем образ через `docker build` при этом указав имя и тег  
![Part_4_4.png](Screenshots/Part_4_4.png)  


* проверяем через `docker images`, что все собралось корректно  
![Part_4_5.png](Screenshots/Part_4_5.png)  


* прежде чем запускать вытащим из образа папку nginx для последующего маппинга  
![Part_4_3.png](Screenshots/Part_4_3.png)  
![Part_4_6.png](Screenshots/Part_4_6.png)  


* Запускаем собранный докер образ с маппингом 81 порта на 80 на локальной машине и маппингом папки ./nginx внутрь контейнера по адресу, где лежат конфигурационные файлы nginx'а  
![Part_4_7.png](Screenshots/Part_4_7.png)  


* проверяем в браузере  
![Part_4_8.png](Screenshots/Part_4_8.png)  


* Дописываем в ./nginx/nginx.conf проксирование странички /status, по которой надо отдавать статус сервера nginx  
![Part_4_9.png](Screenshots/Part_4_9.png)  


* Перезапускаем докер образ, проверяем, заглядываем в браузер  
![Part_4_12.png](Screenshots/Part_4_12.png)  
![Part_4_10.png](Screenshots/Part_4_8.png)  
![Part_4_11.png](Screenshots/Part_4_11.png)  

## Part 5. Dockle  
* сперва установим доклю  
![Part_5_1.png](Screenshots/Part_5_1.png)  


* потом проверим образ  
![Part_5_2.png](Screenshots/Part_5_2.png)  


* C ошибкой CIS-DI-0010 можно было разобраться только сменой образа на Alpine  
* переписываем докерфайл  
![Part_5_4.png](Screenshots/Part_5_4.png)  

* Ошибки устранены
![Part_5_5.png](Screenshots/Part_5_5.png)  

## Part 6. Базовый Docker Compose  
* Перепишем скрипт entrypoint для второго контейнера, иначе он будет завершать работу после `docker-compose up`  
![Part_6_1.png](Screenshots/Part_6_1.png)  


* Перепишем _**nginx.conf**_ для проксирования  
![Part_6_2.png](Screenshots/Part_6_2.png)  


* напишем **_docker-compose.yml_**  
![Part_6_4.png](Screenshots/Part_6_4.png)  


* билдим командой `sudo docker-compose build` 
![Part_6_5.png](Screenshots/Part_6_5.png)  


* запускаем командой `sudo docker-compose up`
![Part_6_6.png](Screenshots/Part_6_6.png)  


* проверяем в браузере

![Part_6_7.png](Screenshots/Part_6_7.png)  
![Part_6_8.png](Screenshots/Part_6_8.png)  
