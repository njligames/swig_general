#!/usr/bin/python
""" 
@package pyVault
   Vault API support for Python scripts
   @author Andrew Osiow
   @date 02/28/2019

   description: basic data collector test for RND without using pyops libs

   Data Collector should be available at this url 
   https://rnd-creator-uv.envrmnt.com/#/mec/remoteServer/

   search for Servers with 'lib_test' catagory filter

"""

import json
import requests
import uuid as u


auth_token = 'eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJ1c2VybWFuYWdlciIsInVzZXIiOnsidWlkIjoidXZVc2VyIiwiZW1haWwiOiJ0ZXN0QGVudnJtbnQuY29tIiwidXNlcm5hbWUiOiJ1dlVzZXIifSwicm9sZXMiOlsiQVJCVUlMREVSIiwiQVNTRVRNQU5BR0VSIiwiV09STERCVUlMREVSIl0sInRlYW0iOnsidWlkIjoidXZVc2VyIiwibmFtZSI6IlRlc3QgVGVhbSJ9LCJhY2Nlc3NUb2tlbiI6ImZha2UiLCJleHAiOjE1NjE1NzA4MDAsImlhdCI6MTUzMDAxNjgxOX0.2vjqRB9COA7uS33ralOUk7z3kH6CdNy6M4lVAVh34djnet6OTSJIMsFzojhR2apX18LIz7dPGqtnx09fc6S3FQu7DEx4Zw7fBtAmlzk7wN3gptM3-xY7P9Lpxs6h7N4es3hysF1VaC7Oow7VJlYlwo1xgzWCR4It2HO-bm6PL6Q62PAJaROUamKr4nmtLA1o4bWKxwnpsC425fpqU_DhESQm1377H50Ins7C9L70fezwB3GmuJ8sYUhxe77PfjaByeWMvdeJqvg2uHcfLb8_wybq0kiGV3HysMIX4WKuOM7veumvk2bX-Lkx-YUuSnR_A_f20pT3pXdCOtyPzLwm8ZONx9gYMwSB24Dlgd2L1OeRP1VBcqymQFAvswO5vMoCz-pZfeg6uWS5WIJUfv6kex1kgaJKvH7QN6wF3WjTK4d9yQxP8kdF8KxH2iOBc0Z3jSaPSS-p3TQorPx3iPhM_y5pm41UfAcV8ClIKgMnO4jxRBBxzhsSAQbnuZP4uqEM0VeNCPNG8quUgA7p6d0jabCsIGcLT9j5lzIMNsEtP23gCjejXBzJeIVH3dgtJssQNAsAy-LIzHHeVA6wIJH-meAzRT_8hO5WM6Cn7OFIaFKUXA7EiqijMdeYvp7i9AJb2F-OrhLNF_5wdM5-PbwtldGQ3Kyq0wiJhiTFYdlfqiA'
vaultHeaders = {
    'Authorization': 'Bearer %s' % auth_token }

baseUrl = 'https://rnd-creator-evrvault-uv.envrmnt.com/'
createDC = 'graphics/api/v1/createStatsCollector'
persistDC = 'graphics/api/v1/updateServerStats'

dc = '{"Layout":{"RootIdx":0,"RootLayoutType":"VLayout","HLayout":[{"Idx":0,"Elements":[{"Type":"Text","Idx":0},{"Type":"Checkbox","Idx":0}]},{"Idx":1,"Elements":[{"Type":"Text","Idx":1},{"Type":"Checkbox","Idx":1}]}],"VLayout":[{"Idx":0,"Elements":[{"Type":"HLayout","Idx":0},{"Type":"HLayout","Idx":1}]}]},"Text":[{"Title":"Line1","Body":"Line 1 goes right here"},{"Title":"s Line2","Body":"and Line 2 goes here"}],"Checkbox":[{"Title":"Like","value":false},{"Title":"Like","value":true}]}'

def main():

    print 'Making Data Collector - Raw'

    dcID = str(u.uuid4())

    print 'Collector id: %s' % dcID
    createDC_url = baseUrl + createDC
    data = {'serverUUID': dcID, 'serverTags': 'lib_test'}

    resp = requests.post(createDC_url, data = data, headers = vaultHeaders)

    if resp.status_code == 200:
        print 'success'
    else:
        print 'createStatsCollector {%s}' % resp.status_code
        print resp.text


    print 'Pesist Data to Collector - Raw'

    command_body = {'serverUUID': dcID,
                    'statsJson': dc}
    persistDC_url = baseUrl + persistDC

    resp = requests.post(persistDC_url, data = command_body, headers = vaultHeaders)    

    if resp.status_code == 200:
        print 'success'
    else:
        print 'pesistCollector {%s}' % resp.status_code
        print resp.text

    print 'Finished'


if __name__ == '__main__':

    main()
