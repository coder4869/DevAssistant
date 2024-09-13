# coding=UTF-8
# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

import os
import json

class PytJson(object):
    @staticmethod
    def load_config(json_config):
        if not os.path.isfile(json_config):
            return None
        with open(json_config, encoding="utf-8") as json_file:
            dic = json.load(json_file)
            json_file.close()
        return dic
