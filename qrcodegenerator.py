import wifi_qrcode_generator.generator

qr_code = wifi_qrcode_generator.generator.wifi_qrcode(ssid='peshal', hidden=False, authentication_type='WPA', password='Pesh@ldaii')
qr_code.print_ascii()
qr_code.make_image().save('qr.png')
