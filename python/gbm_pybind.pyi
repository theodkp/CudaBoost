from typing import List, Optional, Union
import numpy as np
import numpy.typing as npt

class Regressor:

    def __init__(
        self,
        n_estimators: int = 100,
        max_depth: int = 3,
        learning_rate: float = 0.1,
    ) -> None: ...

    def fit(
        self,
        # accepts 2d List or 2d numpy array
        X: Union[List[List[float]], npt.NDArray[np.float32]],
        # accepts 1d List or 1d numpy array
        y: Union[List[float], npt.NDArray[np.float32]]
    
    
    ) -> None: ...

    def predict(
            self,
            X: Union[List[List[float]], npt.NDArray[np.float32]]
    ) -> npt.NDArray[np.float32]: ...
    