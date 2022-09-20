# Rock64_CpuTempOverBrowser

![screenshot](https://user-images.githubusercontent.com/113915726/191049648-1a3bdbfb-a268-4a15-ad81-5a2e4e3825b6.png)

## Purpose
Simple software for monitoring the cpu temperature on a rock64 via browser using chart.js, with 3-day history, simple moving average and low pass filter calculation.

## Usage
This software consists of an html file, the javascript module 'chart.js' and a c file. To set things up copy the 'data' folder to your
http server root directory and adjust the dates within  0_Temperature.csv manually.

Use any http server to host the first two files.
Create a cronjob to periodically execute temp-aarch64 (for example every minute), temperature values will be stored in csv files inside /var/www/data.


## Note to self:
Set up SSH keys for github repo like so:
> 1. create ssh key per `ssh-keygen -t ed25519 -C "your_email@example.com"`, passphrase optional
> 2. run ``eval `ssh-agent -s` ``
> 3. add key to ssh-manager per `ssh-add PRIVATEKEY`
> 4. ready to git
