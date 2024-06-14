from flask import Flask, request, jsonify
from datetime import datetime

app = Flask(__name__)

data = []

@app.route('/')
def home():
    return 'Kelas SIC 2024'

@app.route('/sensor/data', methods=['POST'])
def post_sensor_data():
    content = request.json
    temperature = content['temperature']
    kelembapan = content['kelembapan']
    timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    
    entry = {
        'temperature': temperature,
        'kelembapan': kelembapan,
        'timestamp': timestamp
    }
    
    data.append(entry)
    return jsonify({'message': 'Data berhasil disimpan'}), 200

@app.route('/sensor/data', methods=['GET'])
def get_sensor_data():
    return jsonify(data), 200

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')
