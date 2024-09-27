from flask import Flask, jsonify, request

json_thing = {'direction':None} # sets up dictionary to be edited later on in functions

app = Flask(__name__) # creates instance of flask

def FWD(): 
    json_thing['direction'] = 'forward' 
    print('going forward') # debugging purposes; makes sure api has received the command
    # later on, the code for the robot to go forward also goes here
    return jsonify(json_thing) # returns json data into the main function
    # the function structure + logic is the same for all other movement functions 
    
def BACKWD():
    json_thing['direction'] = 'backward'
    print('going backward') 
    return jsonify(json_thing)

def LEFT():
    json_thing['direction'] = 'left'
    print('going left')
    return jsonify(json_thing)

def RIGHT():
    json_thing['direction'] = 'right'
    print('going right')
    return jsonify(json_thing)

def STOP():
    json_thing['direction'] = 'stop'
    print('stopping')
    return jsonify(json_thing)

@app.route('/',methods=['GET']) # landing page
def default():
    return 'api created by left no scrums'

@app.route('/moving',methods=['POST'])
def direction():
    if request.method == 'POST':
        direction = request.json['direction'] # extracts the direction out of json  
        # runs a function based on which command was posted to api using if-elif 
        if direction == 'forward': 
            result = FWD()
        elif direction == 'backward':
            result = BACKWD()
        elif direction == 'left':
            result = LEFT()
        elif direction == 'right':
            result = RIGHT()
        elif direction == 'stop':
            result = STOP()
        return result # returns json data to url

if __name__ == '__main__':
    app.run(debug=True,host='0.0.0.0') # runs api
