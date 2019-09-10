import boto3
import sys
import zipfile
s3 = boto3.resource('s3')
bucket = s3.Bucket('tf-test-packages')
bucket.download_file('tf-test-packages.zip', '/tmp/tf-test-packages.zip')
with zipfile.ZipFile('/tmp/tf-test-packages.zip') as existing_zip:
    existing_zip.extractall('/tmp/tf-test-packages')

sys.path.append("/tmp/tf-test-packages")

# Surpress warnings. Please unvail these warnings when development.
import warnings
warnings.filterwarnings("ignore", category=RuntimeWarning)
warnings.filterwarnings("ignore", category=FutureWarning)

import time

import argparse
import os
import unicodedata
import boto3

CWD_PATH = os.getcwd()

from core import *

def nazoru_input(data):
    s3 = boto3.resource('s3')
    bucket = s3.Bucket('sano-test')
    bucket.download_file('optimized_nazoru.pb', '/tmp/optimized_nazoru.pb')
    predictor = NazoruPredictor('/tmp/optimized_nazoru.pb')
    result = predictor.predict_top_n(data, 5)
    return result

def main(event, context):
    number = event['queryStringParameters']['data']
    #data = "[a,b,c,d,f]"とかでくることを想定

    result = nazoru_input(data.split(","))

    return {
        'statusCode': 200,
        'body': result
    }
