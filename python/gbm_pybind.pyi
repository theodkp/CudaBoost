from typing import List, Any

class Dataset:
    """Python binding for the C++ Dataset class."""
    
    def __init__(self) -> None:
        """Initialize an empty Dataset."""
        ...
    
    featureNames: List[str]
    """Names of features in the dataset."""
    
    data: List[List[float]]
    """The actual data as a 2D list of floats."""

def load_csv(filename: str) -> Dataset:
    """
    A function to load a CSV file into a Dataset.
    
    Args:
        filename: Path to the CSV file to load
        
    Returns:
        A Dataset object containing the loaded data
    """
    ... 

