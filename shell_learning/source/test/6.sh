#! /bin/bash
# tcp6 0 0 :::22 :::* LISTEN 1267/sshd
netstat -apn | grep sshd | sed -n 's/.*:::\([0-9]*\) .* \([0-9]*\)\/sshd/\1 \2/p'
