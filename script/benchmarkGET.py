import http.client
import argparse
import json
from multiprocessing import Process, Lock
from timeit import default_timer as timer
import csv

def worker(lock, num, args):


    headerCSV='response status'+";"+ 'response'+";"+ 'time in s'

    id = 6

    with open('log.csv', 'w', encoding='UTF8', newline='') as f:
        writer = csv.writer(f)
        writer.writerow([headerCSV])

        for r in range(int(args.requests)):

            with lock:
                print("#",num,": Sending request: ", id)
                id+=1
            start = timer()
            conn = http.client.HTTPConnection(args.server, args.port)
            conn.request("GET", args.endpoint)
            response = conn.getresponse()
            end = timer()
            with lock:
                data = str(response.status) + ";" + str(response.read(),'utf-8')+";"+str(end-start)
                writer.writerow([data])
                print(data)
            conn.close()

if __name__ == "__main__":
    argp = argparse.ArgumentParser()

    group = argp.add_mutually_exclusive_group()

    argp.add_argument('-s', '--server',
                      help='Address of the composer service', required=True)
    argp.add_argument('-pt', '--port',
                      help='Port of the composer service', default=80)
    argp.add_argument('-e', '--endpoint',
                      help='Endpoint to send data', default='')
    group.add_argument('-N', '--requests',
                       help ='Number of requests')
    argp.add_argument('-P', '--producers',
                      help='Number of producer processes to run in parallel', default=1)
    args = argp.parse_args()

    lock = Lock()

    #worker(lock,1,args)
    for n in range(int(args.producers)):
        Process(target=worker, args=(lock,n,args)).start()