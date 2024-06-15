from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/receive_data', methods=['POST'])
def receive_data():
    if request.is_json:
        data = request.json
        temperature = data.get('temperature')
        humidity = data.get('humidity')
        if temperature is None or humidity is None:
            return jsonify({"error": "Invalid data format"}), 400
        print(f"Received temperature: {temperature}, humidity: {humidity}")
        return jsonify({"message": "Data received", "temperature": temperature, "humidity": humidity}), 200
    else:
        return jsonify({"error": "Request must be JSON"}), 400

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
