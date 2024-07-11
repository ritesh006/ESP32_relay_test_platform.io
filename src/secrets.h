#include <pgmspace.h>

#define SECRET
#define THINGNAME "ESP32_RELAY_TEST" // change this

const char WIFI_SSID[] = "Airtel_rite_4613";        // change this
const char WIFI_PASSWORD[] = "Ritesh@123";    // change this
const char AWS_IOT_ENDPOINT[] = "a3l1ajea8huzj-ats.iot.eu-north-1.amazonaws.com"; // change this

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUe0vG9tFbLv8nl66mW+1mMKOmufUwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI0MDcxMTE1NTA1
M1oXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKFYrAm8Zvg5xUoZZ+BL
S1VfoDchk5qeN+xB936DWw0mSJQnWFGNw19rtLTwWSzBF7VcnJelcKDYpRRZ60lO
4EbHwT9M2hkO5HoOQUQr3l79MQZySF5ZevAGmh5iQNHMgQ9MDTrSMKmvTTLuaHsV
u6/a2nIoaEGd6OResQiHKmX1/mwj5Zvudy2eXhTH1LWDwACd1D5xjxCE35kF9dQ/
SjYr9bk1E4U5ZDXERDEomh+RWa9q00Z0mRZQ2EHV8hVH+MDxdcq1ii0ee4DiRcDk
ixLRSnFPEA/Cz9Xc5A71/KBq0yzGyyVbrafTxRJaaaRw1cDcU2UljueOJVyVTRXD
cDMCAwEAAaNgMF4wHwYDVR0jBBgwFoAUTeyh7iICMl2x6y9/M1kq/K+NrTwwHQYD
VR0OBBYEFDA0nlSj8i26OSvN2BLMIdFFtnDcMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQCTLorHcOgAelt2k/QefW2DfWAR
vPJqdDrQwH9HeX5JyLs2F3DqDrkOnAWcJ8yKHf6dCjDRhUK8PsEOqgvsS5V7LAJh
U/Gt9vsbN/BmtRC7vC3tlLFCaZTKr8GUh5MX+e7UDTI2XMlCbJQhHmXidJIlzYZy
vxOOKD0B21sGDSpnwWZFn5IV70B23XYE/DNfplPu1Z4bdIerPkq2Jz+DzPozRTJp
mKJLSut0Lcrvyer0EZ8ow5Dv0ib9BchMbq3MLurcc2uPwYkQFR1jkU+nFl6zyGBG
w5qIWXp2SkAxN2fcRc9qyLV29G750y5uXuciDEBzQTEGS1PKoKwCwypP4fNP
-----END CERTIFICATE-----


 
 
)KEY";

// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEogIBAAKCAQEAoVisCbxm+DnFShln4EtLVV+gNyGTmp437EH3foNbDSZIlCdY
UY3DX2u0tPBZLMEXtVycl6VwoNilFFnrSU7gRsfBP0zaGQ7keg5BRCveXv0xBnJI
Xll68AaaHmJA0cyBD0wNOtIwqa9NMu5oexW7r9racihoQZ3o5F6xCIcqZfX+bCPl
m+53LZ5eFMfUtYPAAJ3UPnGPEITfmQX11D9KNiv1uTUThTlkNcREMSiaH5FZr2rT
RnSZFlDYQdXyFUf4wPF1yrWKLR57gOJFwOSLEtFKcU8QD8LP1dzkDvX8oGrTLMbL
JVutp9PFElpppHDVwNxTZSWO544lXJVNFcNwMwIDAQABAoIBACtOF27NiH2bU96d
jwnea6vQbLofYvSe/reExR7JtsiCu/w3yzaobAXSbMAbunOOqARfhRAWsXIac8RQ
lhwo9X1J5A5PXEJZgu1XoiDf/WFVZ7EpP09DiQGfZAI/sNIep40phmuBOtpwWLIQ
1y4iGSwL+5GkUsc50OZqm+2ECdcvkC1RBEFQThOuS1t7JyWWglj3ZGGdiY2jMswZ
xMDEbIINN0YyolWAb896LAHABMyGv/vczdBPZQivQ2Kg8JW6+CGvAroGEQwYbQED
KAdVpFCL5ZCgQsKQM30evoSwsB8mds61ZLA/HYjaP3ieVn4tqBwdZipNNOuvO1fO
vaMmoVECgYEAzYC52e+9wTn/J0wNDGsLZcZgewKB2Zl0/13mYIgXJdE67BPW+AQ9
ZCW1F6NKLrzBARBkjeKsqkpPixZC2RonQ/be9n+e1XKK0qtnK6e6X5c101lUN28U
SMomHMtxeJi/dDsmh1xN8rQaPc47YtMCKlndcSxVDJCGmjn4qQwamtUCgYEAyP5C
LLRrZnWcQlBc5tfKssetMFpEe1l6WDjYQe0Lr4VfC2akc9BZYw70FR+yXzYNnCQ8
4Z9RNousXWnrA3X3uZUjZxcIdPO47h4o6p3tuALHeVs/7VcVibvIEs5IzfcZR/14
R6lyIAN5mo097C1ha+So3foCf3l2G5SQ+g1D0ucCgYAKaq4BCA/8TW5LlaVLrdlk
DUwysAvY9dhiYWYeGofh2Ns9wDuzUrOx8d9eFV7bQ6Ic5bHTJ1xNPXsOt9AnpRW8
cjUXFZz9gNLcnueZ5OSjl8yYq/yC2tSSY/zOlNlpnYSG5cCsN9eTp+F0pJGKDtwb
PXbmF7Mv8duA0dNy7jQjCQKBgER5UqQWRyydzsFMzYmbZKPpoNgDOKdpQWQC4bH8
BuoiHtIsgsQt6/XyZzc3GDaVnKdgNRmMhEd36B3e8sC4FNA1vdzmHOxzB8KfpcLg
UNdKoxh1/N5nt5+3yJ6XhngcwZEkCjEnygicBnafvcPTZggy21DcVrOE9rbIs2ds
03lrAoGAeuVVFd4xm2j5qwxJAQe7h2QhNF2UUGS5DUjbNYWLo19lP/qQ+Aej390a
6C9mJjbeuEp37jKePC40ph0HH4ruCUriPW/pwKAoupy/OtTw8geUvf5FB+SU2O9Y
bdBDQIC+4eoHLKYBHfzsdKc8rQ+WKXw99SeEuoQNdsF5vNtDCkE=
-----END RSA PRIVATE KEY-----


 
)KEY";