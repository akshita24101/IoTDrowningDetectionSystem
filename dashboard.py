import streamlit as st
import requests
import datetime

# ThingSpeak Info
CHANNEL_ID = "your_channel_id"
READ_API_KEY = "your_API_key"  # Replace with your Read API Key
URL = f"https://api.thingspeak.com/channels/{your_channel_id}/feeds.json?api_key={your_API_key}&results=10"

# Page setup
st.set_page_config(page_title="Drowning Detection System", layout="centered")

# Custom styling
st.markdown("""
    <style>
        body {
            background-color: #4994de;
        }
        .stApp {
            background-color: #4994de;
        }
        h1 {
            text-align: center;
            color:#063869;
            font-size: 40px;
            margin-bottom: 0.2em;
        }
        .description {
            text-align: center;
            color: #063869;
            font-size: 22px;
            margin-top: 0.1em;
        }
        .data-section {
            margin-top: 2em;
        }
    </style>
""", unsafe_allow_html=True)

# Title and description
st.markdown("<h1>Drowning Detection System</h1>", unsafe_allow_html=True)
st.markdown('<p class="description">An IoT-based safety system using Arduino and ESP8266.</p>', unsafe_allow_html=True)
st.markdown('<p class="description">It continuously monitors motion and distance to detect possible drowning incidents.</p>', unsafe_allow_html=True)

# Fetch ThingSpeak data
try:
    response = requests.get(URL)
    data = response.json()

    if "feeds" not in data or len(data["feeds"]) == 0:
        st.error("No data received from ThingSpeak.")
    else:
        feeds = data["feeds"]

        st.markdown('<div class="data-section">', unsafe_allow_html=True)
        st.subheader("Live Sensor Readings")

        latest = feeds[-1]
        col1, col2, col3 = st.columns(3)
        col1.metric("Distance (cm)", latest["field1"])
        col2.metric("PIR Motion", "Detected" if latest["field2"] == "1" else "None")
        col3.metric("Status", "DROWNING" if latest["field3"] == "1" else "SAFE")

        st.markdown("---")
        st.subheader("Recent Data Logs")

        table_data = []
        for feed in reversed(feeds):
            try:
                time = datetime.datetime.strptime(feed["created_at"], "%Y-%m-%dT%H:%M:%SZ")
                table_data.append({
                    "Time": time.strftime("%H:%M:%S"),
                    "Distance (cm)": feed["field1"],
                    "PIR": "Motion" if feed["field2"] == "1" else "No Motion",
                    "Drowning": "Yes" if feed["field3"] == "1" else "No"
                })
            except:
                continue

        st.dataframe(table_data, use_container_width=True)
        st.markdown('</div>', unsafe_allow_html=True)

except Exception as e:
    st.error(f"Error fetching data: {e}")

#this is a code for launching on local host. Run on command prompt accordingly.
