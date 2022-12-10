# coding=UTF-8

import os
import json

class PytJson(object):
    @staticmethod
    def load_config(json_config):
        if not os.path.isfile(json_config):
            return None
        with open(json_config) as json_file:
            dic = json.load(json_file)
            json_file.close()
        return dic
