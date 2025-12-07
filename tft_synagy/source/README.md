apache2を使用するためapache2をインストールする

手順
1 sudo apt update
2 sudo apt install apache2

apache2のcgiを使うので設定する

手順
1 sudo a2enmod cgi
2 sudo systemctl restart apache2

実行できない場合は　chmod 755 /usr/lib/cgi-bin/main.cgi　をして実行権限を与える
