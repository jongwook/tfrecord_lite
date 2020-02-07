import io
import os

import numpy as np
from PIL import Image
from tfrecord_lite import *

pwd = os.path.dirname(__file__)


def test_length():
    iterator = tf_record_iterator(os.path.join(pwd, "test.tfrecord"))
    assert len(list(iterator)) == 42


def test_images():
    for record in tf_record_iterator(os.path.join(pwd, "images.tfrecord")):
        height, width, depth = record["height"], record["width"], record["depth"]

        image_raw = record["image_raw"][0]
        image = Image.open(io.BytesIO(image_raw))
        image = np.array(image)

        assert height == image.shape[0]
        assert width == image.shape[1]

        if depth > 1:
            assert depth == image.shape[2]
