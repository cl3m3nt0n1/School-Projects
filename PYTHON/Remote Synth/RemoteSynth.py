import socket
import pygame
import numpy as np
import tkinter as tk
from tkinter import ttk
import threading
import re


class OSC:
    def __init__(self):
        pygame.init()
        pygame.mixer.init()
        self.frequencies = [261.33, 293.66, 329.63, 349.23, 392, 440, 493.88]

    def generate_lfo(self, frequency, duration, sample_rate):
        t = np.arange(sample_rate * duration)
        lfo_wave = np.sin(2 * np.pi * frequency * t / sample_rate)
        return lfo_wave.astype(np.int16)

    def generate_ad_envelope(self, attack_duration, decay_duration, sample_rate):
        attack_samples = int(sample_rate * attack_duration)
        decay_samples = int(sample_rate * decay_duration)
        envelope = np.zeros(attack_samples + decay_samples)
        envelope[:attack_samples] = np.linspace(0, 32767, attack_samples)  # Attack
        envelope[attack_samples:attack_samples + decay_samples] = np.linspace(32767, 0, decay_samples)  # Decay
        return envelope.astype(np.int16)

    def generate_sin_wave(self, frequency, amplitude, duration, sample_rate):
        t = np.arange(duration)
        sin_wave =  1.01 * np.sin(2 * np.pi * frequency * t / sample_rate)
        return (sin_wave).astype(np.int16)

    def generate_square_wave(self, frequency, amplitude, duration, sample_rate):
        t = np.arange(duration)
        square_wave = np.sign(np.sin(2 * np.pi * frequency * t / sample_rate))
        return (square_wave).astype(np.int16)

    def generate_triangle_wave(self, frequency, amplitude, duration, sample_rate):
        t = np.arange(duration)
        triangle_wave = np.cumsum(np.sign(np.sin(2 * np.pi * frequency * t / sample_rate)))
        return (1.01 * triangle_wave).astype(np.int16)

    def generate_sawtooth_wave(self, frequency, amplitude, duration, sample_rate):
        t = np.arange(duration)
        sawtooth_wave = 2 * (t % (sample_rate // frequency)) / (sample_rate // frequency) - 1
        return ( 2 * sawtooth_wave).astype(np.int16)

    def play_sound_with_lfo(self, frequency, amplitude, duration, sample_rate, lfo_frequency, channel_id=None,
                            type="sine"):
        lfo_wave = self.generate_lfo(lfo_frequency, duration, sample_rate)
        if (type == "sine"):
            wave = self.generate_sin_wave(frequency, amplitude, duration, sample_rate)
        if (type == "square"):
            wave = self.generate_square_wave(frequency, amplitude, duration, sample_rate)
        if (type == "tri"):
            wave = self.generate_triangle_wave(frequency, amplitude, duration, sample_rate)
        if (type == "saw"):
            wave = self.generate_sawtooth_wave(frequency, amplitude, duration, sample_rate)

        modulated_wave = wave * (1 + lfo_wave)  # Modifier l'amplitude
        stereo_wave = np.column_stack((modulated_wave, modulated_wave))
        buffer = pygame.sndarray.make_sound(stereo_wave)
        if channel_id is None:
            channel = pygame.mixer.find_channel()
        else:
            channel = pygame.mixer.Channel(channel_id)
        if not channel.get_busy():
            channel.play(buffer)

    def play_sound(self, frequency, amplitude, sample_rate, channel_id=None, type="sine", attack=0.1, decay=0.1):

        envelope = self.generate_ad_envelope(attack, decay, sample_rate)

        if (type == "sine"):
            wave = self.generate_sin_wave(frequency, amplitude, len(envelope), sample_rate)
        if (type == "square"):
            wave = self.generate_square_wave(frequency, amplitude, len(envelope), sample_rate)
        if (type == "tri"):
            wave = self.generate_triangle_wave(frequency, amplitude, len(envelope), sample_rate)
        if (type == "saw"):
            wave = self.generate_sawtooth_wave(frequency, amplitude, len(envelope), sample_rate)

        enveloped_wave = wave * envelope
        stereo_wave = np.column_stack((enveloped_wave, enveloped_wave))
        buffer = pygame.sndarray.make_sound(stereo_wave)
        if channel_id is None:
            channel = pygame.mixer.find_channel()
        else:
            channel = pygame.mixer.Channel(channel_id)
        if not channel.get_busy():
            channel.play(buffer)

    def process(self, data, channel_id, type, lfo_state=False, lfo_freq=2, sample_rate=44100, attack=0.1, decay=0.1):
        frequency = self.frequencies[data]
        amplitude = 32767
        amplitude = int(amplitude)

        if (bool(lfo_state) == True):
            self.play_sound_with_lfo(frequency, amplitude, sample_rate, lfo_freq, channel_id, type)
        elif bool(lfo_state) == False:
            self.play_sound(frequency, amplitude, sample_rate, channel_id, type, attack=attack, decay=decay)


class GUI:
    def __init__(self, osc):
        self.osc = osc
        self.root = tk.Tk()
        self.root.title("Remote controlled python Synth")
        self.wave_type_var = tk.StringVar(self.root, "sine")
        self.lfo_enabled_var = tk.BooleanVar(value=False)
        self.lfo_frequency_var = tk.DoubleVar(value=0.1)
        self.attack_duration_var = tk.DoubleVar(value=0.01)
        self.decay_duration_var = tk.DoubleVar(value=0.1)

        # Potentiomètres pour duration et sample_rate
        self.duration_var = tk.DoubleVar(value=0.1)
        self.sample_rate_var = tk.IntVar(value=44100)


        # Ajout des boutons radio pour le choix de la forme d'onde
        wave_type_dict = {
            "Sinus": "sine",
            "Carré": "square",
            "Triangulaire": "tri",
            "Dents de scie": "saw"
        }

        i = 0
        for text, value in wave_type_dict.items():
            ttk.Radiobutton(self.root, text=text, variable=self.wave_type_var, value=value).grid(row=4 + i, column=1,
                                                                                                 sticky='w')
            i += 1

        # ttk.Label(self.root, text="Duration (s)").grid(row=0, column=0)
        # ttk.Scale(self.root, from_=0.01, to=1.0, variable=self.duration_var, length=200).grid(row=0, column=1)

        ttk.Label(self.root, text="Sample Rate (Hz)").grid(row=1, column=0)
        ttk.Scale(self.root, from_=1000, to=44100, variable=self.sample_rate_var, length=200).grid(row=1, column=1)

        ttk.Label(self.root, text="Envelope Attack").grid(row=2, column=0)
        ttk.Scale(self.root, from_=0.1, to=1, variable=self.attack_duration_var, length=200).grid(row=2, column=1)

        ttk.Label(self.root, text="Envelope Decay").grid(row=3, column=0)
        ttk.Scale(self.root, from_=0.1, to=5, variable=self.decay_duration_var, length=200).grid(row=3, column=1)

        # ttk.Checkbutton(self.root, text="Activer LFO", variable=self.lfo_enabled_var).grid(row=4, column=0, sticky='w')

        # ttk.Label(self.root, text="Fréquence LFO (Hz)").grid(row=3, column=0)
        # ttk.Scale(self.root, from_=0.01, to=10.0, variable=self.lfo_frequency_var, length=200).grid(row=3, column=1)

        # Bouton pour démarrer le serveur
        ttk.Button(self.root, text="Start Server", command=self.start_server).grid(row=8, column=0, columnspan=2)

    def start_server(self):
        # Démarrer le serveur dans un thread séparé
        server_thread = threading.Thread(target=self.run_server)
        server_thread.start()

    def run_server(self):
        HOST = "172.20.10.4"
        PORT = 2020

        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.bind((HOST, PORT))
            s.listen()
            conn, addr = s.accept()
            with conn:
                print(f"Connected by {addr}")
                while True:
                    data = conn.recv(4).decode('utf-8')
                    if not data:
                        print("Interrupted by client")
                        break
                    try:
                        # Utiliser une expression régulière pour extraire x et value
                        match = re.match(r'@(\d+)/(\d+)', data)
                        if match:
                            x = int(match.group(1))
                            value = int(match.group(2))
                            if 1 <= x <= 7:
                                if value > 0:
                                    channel_id = x - 1  # Utiliser x -  1 comme identifiant de canal
                                    self.osc.process(x,
                                                     channel_id=channel_id,
                                                     type=self.wave_type_var.get(),
                                                     lfo_state=bool(self.lfo_enabled_var.get()),
                                                     lfo_freq=self.lfo_frequency_var.get(),
                                                     sample_rate=self.sample_rate_var.get(),
                                                     attack=self.attack_duration_var.get(),
                                                     decay=self.decay_duration_var.get())
                            else:
                                print("Valeur de x invalide")
                    except Exception as e:
                        print(f"Error processing data: {e}")
                        break

    def run(self):
        self.root.mainloop()


# Initialiser Pygame et le mixer
pygame.init()
pygame.mixer.init()

# Créer une instance de la classe OSC
osc = OSC()

# Créer et lancer la GUI
gui = GUI(osc)
gui.run()

# Terminer Pygame
pygame.quit()
