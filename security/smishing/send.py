#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
from twilio.rest import Client

account_sid = os.environ["SMISHING_ACCOUNT_SID"]
auth_token = os.environ["SMISHING_AUTH_TOKEN"]
from = os.environ["SMISHING_FROM"] # '+01234567890'
to = os.environ["SMISHING_TO"] # '+81012345678990'

client = Client(account_sid, auth_token)
message = client.messages.create(
    body=("-\nAmazon Pay キャッシュバックキャンペーンに当選しました。\n\n"
          "下記のリンクからログインして1万円分のポイントをご利用ください。\n"
          "https://example.com/"),
    from_=from,
    to='to'
)
