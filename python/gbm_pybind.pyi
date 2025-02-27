from typing import List, Optional, Union
import numpy as np
import numpy.typing as npt

class Regressor:
    n_estimators: int
    max_depth: int
    learning_rate: float
    n_bins: int
    device: str

    def __init__(
        self,
        n_estimators: int = 100,
        max_depth: int = 3,
        learning_rate: float = 0.1,
        n_bins: int = 256,
        device: str = "cpu"
    ) -> None: ...

    def fit(
        self,
        # accepts 2d List or 2d numpy array
        X: Union[List[List[float]], npt.NDArray[np.float32]],
        # accepts 1d List or 1d numpy array
        y: Union[List[float], npt.NDArray[np.float32]]
    ) -> None: ... 

