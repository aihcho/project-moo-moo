import requests
import sys

webhook_url = 'https://maker.ifttt.com/trigger/motion/with/key/kRLN1DkKFq-kliji8lNDX'

r = requests.post(webhook_url)

sys.exit()


