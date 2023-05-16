#!/usr/bin/env python
# -*- coding: utf-8 -*-
import pings
p = pings.Ping()

if __name__ == '__main__':
    response = p.ping("baidu.com")
    response.print_messages()

