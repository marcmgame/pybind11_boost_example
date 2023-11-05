
rm -rf build

git submodule update --init --recursive
pip uninstall -y boost_example &> /dev/null || true
pip install . --upgrade --no-deps --force-reinstall --no-cache-dir $@
